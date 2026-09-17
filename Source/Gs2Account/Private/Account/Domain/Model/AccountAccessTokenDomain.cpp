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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"
#include "Account/Domain/Model/TakeOverTypeModel.h"
#include "Account/Domain/Model/TakeOverTypeModelMaster.h"
#include "Account/Domain/Model/CurrentModelMaster.h"

#include "Account/Model/Cache/PlatformId.h"
#include "Account/Model/Cache/TakeOver.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Account::Domain::Model
{

    FAccountAccessTokenDomain::FAccountAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Account"
        ))
    {
    }

    FAccountAccessTokenDomain::FAccountAccessTokenDomain(
        const FAccountAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FAccountAccessTokenDomain::FDeleteTakeOverTask::FDeleteTakeOverTask(
        const TSharedPtr<FAccountAccessTokenDomain>& Self,
        const Request::FDeleteTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountAccessTokenDomain::FDeleteTakeOverTask::FDeleteTakeOverTask(
        const FDeleteTakeOverTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountAccessTokenDomain::FDeleteTakeOverTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DeleteTakeOver(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            if (!Future->GetTask().Error()->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                return Future->GetTask().Error();
            }
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr && ResultModel->GetItem() != nullptr)
        {
            Gs2::Account::Model::Cache::FTakeOverCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                CacheOwnerUserId,
                ResultModel->GetItem()->GetType().Get(0),
                CacheOwnerTimeOffset
            );
        }
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel != nullptr && ResultModel->GetItem() != nullptr ? ResultModel->GetItem()->GetType() : TOptional<int32>()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccountAccessTokenDomain::FDeleteTakeOverTask>> FAccountAccessTokenDomain::DeleteTakeOver(
        Request::FDeleteTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTakeOverTask>>(this->AsShared(), Request);
    }

    Gs2::Account::Domain::Iterator::FDescribeTakeOversIteratorPtr FAccountAccessTokenDomain::TakeOvers(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FAccountAccessTokenDomain::SubscribeTakeOvers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FAccountAccessTokenDomain::UnsubscribeTakeOvers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FAccountAccessTokenDomain::FCollectTakeOversTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Account::Model::FTakeOverPtr>>, public TSharedFromThis<FCollectTakeOversTask>
    {
        const TSharedPtr<FAccountAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Account::Model::FTakeOverPtr>)> OnCollected;

    public:
        explicit FCollectTakeOversTask(const TSharedPtr<FAccountAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectTakeOversTask(const FCollectTakeOversTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Account::Model::FTakeOverPtr>>> Result) override
        {
            TArray<Gs2::Account::Model::FTakeOverPtr> Items;
            auto Iterator = Self->TakeOvers()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Account::Model::FTakeOverPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FAccountAccessTokenDomain::SubscribeTakeOvers(
        TFunction<void(TArray<Gs2::Account::Model::FTakeOverPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Account::Model::FTakeOver::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Account::Model::FTakeOverPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Account::Model::FTakeOver>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FAccountAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTakeOversTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FAccountAccessTokenDomain::InvalidateTakeOvers()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Account::Model::FTakeOver::TypeName,
            Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FAccountAccessTokenDomain::FSubscribeTakeOversWithInitialCallTask::FSubscribeTakeOversWithInitialCallTask(const TSharedPtr<FAccountAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FAccountAccessTokenDomain::FSubscribeTakeOversWithInitialCallTask::FSubscribeTakeOversWithInitialCallTask(const FSubscribeTakeOversWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FAccountAccessTokenDomain::FSubscribeTakeOversWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTakeOversTask>>(Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeTakeOvers(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FAccountAccessTokenDomain::FSubscribeTakeOversWithInitialCallTask>> FAccountAccessTokenDomain::SubscribeTakeOversWithInitialCall(TFunction<void(TArray<Gs2::Account::Model::FTakeOverPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTakeOversWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain> FAccountAccessTokenDomain::TakeOver(
        const int32 Type
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            Type
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerAccessTokenDomain> FAccountAccessTokenDomain::DataOwner(
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FDataOwnerAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Account::Domain::Iterator::FDescribePlatformIdsIteratorPtr FAccountAccessTokenDomain::PlatformIds(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Iterator::FDescribePlatformIdsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FAccountAccessTokenDomain::SubscribePlatformIds(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Account::Model::FPlatformId::TypeName,
            Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FAccountAccessTokenDomain::UnsubscribePlatformIds(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Account::Model::FPlatformId::TypeName,
            Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FAccountAccessTokenDomain::FCollectPlatformIdsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Account::Model::FPlatformIdPtr>>, public TSharedFromThis<FCollectPlatformIdsTask>
    {
        const TSharedPtr<FAccountAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Account::Model::FPlatformIdPtr>)> OnCollected;

    public:
        explicit FCollectPlatformIdsTask(const TSharedPtr<FAccountAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FPlatformIdPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectPlatformIdsTask(const FCollectPlatformIdsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Account::Model::FPlatformIdPtr>>> Result) override
        {
            TArray<Gs2::Account::Model::FPlatformIdPtr> Items;
            auto Iterator = Self->PlatformIds()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Account::Model::FPlatformIdPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FAccountAccessTokenDomain::SubscribePlatformIds(
        TFunction<void(TArray<Gs2::Account::Model::FPlatformIdPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Account::Model::FPlatformId::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Account::Model::FPlatformIdPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Account::Model::FPlatformId>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FAccountAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectPlatformIdsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FAccountAccessTokenDomain::InvalidatePlatformIds()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Account::Model::FPlatformId::TypeName,
            Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FAccountAccessTokenDomain::FSubscribePlatformIdsWithInitialCallTask::FSubscribePlatformIdsWithInitialCallTask(const TSharedPtr<FAccountAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FPlatformIdPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FAccountAccessTokenDomain::FSubscribePlatformIdsWithInitialCallTask::FSubscribePlatformIdsWithInitialCallTask(const FSubscribePlatformIdsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FAccountAccessTokenDomain::FSubscribePlatformIdsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectPlatformIdsTask>>(Self, TFunction<void(TArray<Gs2::Account::Model::FPlatformIdPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribePlatformIds(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FAccountAccessTokenDomain::FSubscribePlatformIdsWithInitialCallTask>> FAccountAccessTokenDomain::SubscribePlatformIdsWithInitialCall(TFunction<void(TArray<Gs2::Account::Model::FPlatformIdPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribePlatformIdsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain> FAccountAccessTokenDomain::PlatformId(
        const int32 Type
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            Type
        );
    }

    FString FAccountAccessTokenDomain::CreateCacheParentKey(
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

    FString FAccountAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }

    FAccountAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FAccountAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FAccountAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FAccount>> Result
    )
    {
        const FString CacheKey = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
            Self->UserId()
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FAccount::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Account::Model::FAccount> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FAccount>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FAccountAccessTokenDomain::FModelTask>> FAccountAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAccountAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAccountAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FAccountPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FAccount::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                UserId()
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FAccount>(obj));
            }
        );
    }

    void FAccountAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FAccount::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                UserId()
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
