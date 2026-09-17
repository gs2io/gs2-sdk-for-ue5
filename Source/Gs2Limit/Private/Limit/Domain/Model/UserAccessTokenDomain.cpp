/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Limit/Domain/Model/UserAccessToken.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"
#include "Limit/Model/Cache/Counter.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Limit::Domain::FGs2LimitDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Limit::Domain::Iterator::FDescribeCountersIteratorPtr FUserAccessTokenDomain::Counters(
        const TOptional<FString> LimitName
    ) const
    {
        return MakeShared<Gs2::Limit::Domain::Iterator::FDescribeCountersIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            LimitName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeCounters(
    TFunction<void()> Callback
        , const TOptional<FString> LimitName
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeCounters(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> LimitName
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectCountersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Limit::Model::FCounterPtr>>, public TSharedFromThis<FCollectCountersTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> OnCollected;
    const TOptional<FString> QueryLimitName;
    public:
        explicit FCollectCountersTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> OnCollected,const TOptional<FString> LimitName) : Self(Self), OnCollected(OnCollected), QueryLimitName(LimitName) {}
        FCollectCountersTask(const FCollectCountersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryLimitName(From.QueryLimitName) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Limit::Model::FCounterPtr>>> Result) override
        {
            TArray<Gs2::Limit::Model::FCounterPtr> Items;
            auto Iterator = Self->Counters(QueryLimitName)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Limit::Model::FCounterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeCounters(
        TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> Callback,const TOptional<FString> LimitName
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Limit::Domain::FGs2LimitDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryLimitName = LimitName;
        const auto Parent = Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Limit::Model::FCounter::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Limit::Model::FCounterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Limit::Model::FCounter>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryLimitName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountersTask>>(Domain, Callback, QueryLimitName);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateCounters(const TOptional<FString> LimitName)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Limit::Model::FCounter::TypeName,
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeCountersWithInitialCallTask::FSubscribeCountersWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> Callback,const TOptional<FString> LimitName) : Self(Self), Callback(Callback), QueryLimitName(LimitName) {}
    FUserAccessTokenDomain::FSubscribeCountersWithInitialCallTask::FSubscribeCountersWithInitialCallTask(const FSubscribeCountersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryLimitName(From.QueryLimitName) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeCountersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountersTask>>(Self, TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)>(), QueryLimitName);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeCounters(Callback, QueryLimitName);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeCountersWithInitialCallTask>> FUserAccessTokenDomain::SubscribeCountersWithInitialCall(TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> Callback,const TOptional<FString> LimitName)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeCountersWithInitialCallTask>>(this->AsShared(), Callback, LimitName);
    }

    TSharedPtr<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain> FUserAccessTokenDomain::Counter(
        const FString LimitName,
        const FString CounterName
    )
    {
        return MakeShared<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            LimitName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LimitName),
            CounterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CounterName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
