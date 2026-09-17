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

#include "Exchange/Domain/Model/UserAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"
#include "Exchange/Model/Cache/RateModel.h"
#include "Exchange/Model/Cache/IncrementalRateModel.h"
#include "Exchange/Model/Cache/Await.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomain> FUserAccessTokenDomain::Exchange(
    )
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIteratorPtr FUserAccessTokenDomain::Awaits(
        const TOptional<FString> RateName
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RateName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeAwaits(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Exchange::Model::FAwait::TypeName,
            Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeAwaits(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Exchange::Model::FAwait::TypeName,
            Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectAwaitsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Exchange::Model::FAwaitPtr>>, public TSharedFromThis<FCollectAwaitsTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> OnCollected;
    const TOptional<FString> QueryRateName;
    public:
        explicit FCollectAwaitsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> OnCollected,const TOptional<FString> RateName) : Self(Self), OnCollected(OnCollected), QueryRateName(RateName) {}
        FCollectAwaitsTask(const FCollectAwaitsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryRateName(From.QueryRateName) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Exchange::Model::FAwaitPtr>>> Result) override
        {
            TArray<Gs2::Exchange::Model::FAwaitPtr> Items;
            auto Iterator = Self->Awaits(QueryRateName)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Exchange::Model::FAwaitPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeAwaits(
        TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> Callback,const TOptional<FString> RateName
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Exchange::Domain::FGs2ExchangeDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRateName = RateName;
        const auto Parent = Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Exchange::Model::FAwait::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Exchange::Model::FAwaitPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Exchange::Model::FAwait>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRateName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAwaitsTask>>(Domain, Callback, QueryRateName);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateAwaits(const TOptional<FString> RateName)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Exchange::Model::FAwait::TypeName,
            Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeAwaitsWithInitialCallTask::FSubscribeAwaitsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> Callback,const TOptional<FString> RateName) : Self(Self), Callback(Callback), QueryRateName(RateName) {}
    FUserAccessTokenDomain::FSubscribeAwaitsWithInitialCallTask::FSubscribeAwaitsWithInitialCallTask(const FSubscribeAwaitsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryRateName(From.QueryRateName) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeAwaitsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAwaitsTask>>(Self, TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)>(), QueryRateName);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeAwaits(Callback, QueryRateName);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeAwaitsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeAwaitsWithInitialCall(TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> Callback,const TOptional<FString> RateName)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAwaitsWithInitialCallTask>>(this->AsShared(), Callback, RateName);
    }

    TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain> FUserAccessTokenDomain::Await(
        const FString AwaitName
    )
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            AwaitName == TEXT("") ? TOptional<FString>() : TOptional<FString>(AwaitName)
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
