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

#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Domain/Model/BalanceParameterModelMaster.h"
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/CurrentParameterMaster.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/BalanceParameterStatus.h"
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"
#include "Enchant/Model/Cache/BalanceParameterStatus.h"
#include "Enchant/Model/Cache/RarityParameterStatus.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterStatusesIteratorPtr FUserAccessTokenDomain::BalanceParameterStatuses(
        const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterStatusesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            ParameterName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeBalanceParameterStatuses(
    TFunction<void()> Callback, const TOptional<FString> ParameterName
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Enchant::Model::FBalanceParameterStatus::TypeName,
            Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeBalanceParameterStatuses(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> ParameterName
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FBalanceParameterStatus::TypeName,
            Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectBalanceParameterStatusesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>>, public TSharedFromThis<FCollectBalanceParameterStatusesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> OnCollected;
    const TOptional<FString> QueryParameterName;
    public:
        explicit FCollectBalanceParameterStatusesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> OnCollected,const TOptional<FString> ParameterName) : Self(Self), OnCollected(OnCollected), QueryParameterName(ParameterName) {}
        FCollectBalanceParameterStatusesTask(const FCollectBalanceParameterStatusesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryParameterName(From.QueryParameterName) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>>> Result) override
        {
            TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr> Items;
            auto Iterator = Self->BalanceParameterStatuses(QueryParameterName)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeBalanceParameterStatuses(
        TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Enchant::Domain::FGs2EnchantDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryParameterName = ParameterName;
        const auto Parent = Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Enchant::Model::FBalanceParameterStatus::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Enchant::Model::FBalanceParameterStatus>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryParameterName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBalanceParameterStatusesTask>>(Domain, Callback, QueryParameterName);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateBalanceParameterStatuses(const TOptional<FString> ParameterName)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Enchant::Model::FBalanceParameterStatus::TypeName,
            Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeBalanceParameterStatusesWithInitialCallTask::FSubscribeBalanceParameterStatusesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName) : Self(Self), Callback(Callback), QueryParameterName(ParameterName) {}
    FUserAccessTokenDomain::FSubscribeBalanceParameterStatusesWithInitialCallTask::FSubscribeBalanceParameterStatusesWithInitialCallTask(const FSubscribeBalanceParameterStatusesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryParameterName(From.QueryParameterName) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeBalanceParameterStatusesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBalanceParameterStatusesTask>>(Self, TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)>(), QueryParameterName);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeBalanceParameterStatuses(Callback, QueryParameterName);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeBalanceParameterStatusesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeBalanceParameterStatusesWithInitialCall(TFunction<void(TArray<Gs2::Enchant::Model::FBalanceParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeBalanceParameterStatusesWithInitialCallTask>>(this->AsShared(), Callback, ParameterName);
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterStatusAccessTokenDomain> FUserAccessTokenDomain::BalanceParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    )
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FBalanceParameterStatusAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName),
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
        );
    }

    Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterStatusesIteratorPtr FUserAccessTokenDomain::RarityParameterStatuses(
        const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterStatusesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            ParameterName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeRarityParameterStatuses(
    TFunction<void()> Callback, const TOptional<FString> ParameterName
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            Gs2::Enchant::Model::Cache::FRarityParameterStatusCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeRarityParameterStatuses(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> ParameterName
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            Gs2::Enchant::Model::Cache::FRarityParameterStatusCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectRarityParameterStatusesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>>, public TSharedFromThis<FCollectRarityParameterStatusesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> OnCollected;
    const TOptional<FString> QueryParameterName;
    public:
        explicit FCollectRarityParameterStatusesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> OnCollected,const TOptional<FString> ParameterName) : Self(Self), OnCollected(OnCollected), QueryParameterName(ParameterName) {}
        FCollectRarityParameterStatusesTask(const FCollectRarityParameterStatusesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryParameterName(From.QueryParameterName) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>>> Result) override
        {
            TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr> Items;
            auto Iterator = Self->RarityParameterStatuses(QueryParameterName)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeRarityParameterStatuses(
        TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Enchant::Domain::FGs2EnchantDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryParameterName = ParameterName;
        const auto Parent = Gs2::Enchant::Model::Cache::FRarityParameterStatusCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryParameterName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRarityParameterStatusesTask>>(Domain, Callback, QueryParameterName);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateRarityParameterStatuses(const TOptional<FString> ParameterName)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            Gs2::Enchant::Model::Cache::FRarityParameterStatusCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeRarityParameterStatusesWithInitialCallTask::FSubscribeRarityParameterStatusesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName) : Self(Self), Callback(Callback), QueryParameterName(ParameterName) {}
    FUserAccessTokenDomain::FSubscribeRarityParameterStatusesWithInitialCallTask::FSubscribeRarityParameterStatusesWithInitialCallTask(const FSubscribeRarityParameterStatusesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryParameterName(From.QueryParameterName) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeRarityParameterStatusesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRarityParameterStatusesTask>>(Self, TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)>(), QueryParameterName);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRarityParameterStatuses(Callback, QueryParameterName);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeRarityParameterStatusesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeRarityParameterStatusesWithInitialCall(TFunction<void(TArray<Gs2::Enchant::Model::FRarityParameterStatusPtr>)> Callback,const TOptional<FString> ParameterName)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRarityParameterStatusesWithInitialCallTask>>(this->AsShared(), Callback, ParameterName);
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusAccessTokenDomain> FUserAccessTokenDomain::RarityParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    )
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FRarityParameterStatusAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName),
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
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
