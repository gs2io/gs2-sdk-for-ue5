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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Limit::Domain::FGs2LimitDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Limit::Domain::Iterator::FDescribeCountersByUserIdIteratorPtr FUserDomain::Counters(
        const TOptional<FString> LimitName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Limit::Domain::Iterator::FDescribeCountersByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            LimitName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeCounters(
    TFunction<void()> Callback
        , const TOptional<FString> LimitName
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeCounters(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> LimitName, const TOptional<FString> TimeOffsetToken
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectCountersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Limit::Model::FCounterPtr>>, public TSharedFromThis<FCollectCountersTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> OnCollected;
    const TOptional<FString> QueryLimitName;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectCountersTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> OnCollected,const TOptional<FString> LimitName,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryLimitName(LimitName), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectCountersTask(const FCollectCountersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryLimitName(From.QueryLimitName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Limit::Model::FCounterPtr>>> Result) override
        {
            TArray<Gs2::Limit::Model::FCounterPtr> Items;
            auto Iterator = Self->Counters(QueryLimitName, QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeCounters(
        TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> Callback,const TOptional<FString> LimitName,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Limit::Domain::FGs2LimitDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryLimitName = LimitName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryLimitName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountersTask>>(Domain, Callback, QueryLimitName, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateCounters(const TOptional<FString> LimitName,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Limit::Model::FCounter::TypeName,
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeCountersWithInitialCallTask::FSubscribeCountersWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> Callback,const TOptional<FString> LimitName,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryLimitName(LimitName), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeCountersWithInitialCallTask::FSubscribeCountersWithInitialCallTask(const FSubscribeCountersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryLimitName(From.QueryLimitName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeCountersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectCountersTask>>(Self, TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)>(), QueryLimitName, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeCounters(Callback, QueryLimitName, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeCountersWithInitialCallTask>> FUserDomain::SubscribeCountersWithInitialCall(TFunction<void(TArray<Gs2::Limit::Model::FCounterPtr>)> Callback,const TOptional<FString> LimitName,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeCountersWithInitialCallTask>>(this->AsShared(), Callback, LimitName, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Limit::Domain::Model::FCounterDomain> FUserDomain::Counter(
        const FString LimitName,
        const FString CounterName
    )
    {
        return MakeShared<Gs2::Limit::Domain::Model::FCounterDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            LimitName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LimitName),
            CounterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(CounterName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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
