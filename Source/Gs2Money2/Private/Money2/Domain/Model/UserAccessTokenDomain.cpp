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

#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/SubscriptionStatus.h"
#include "Money2/Domain/Model/SubscriptionStatusAccessToken.h"
#include "Money2/Domain/Model/RefundHistory.h"
#include "Money2/Domain/Model/StoreContentModel.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModel.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModelMaster.h"
#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/UnusedBalance.h"
#include "Money2/Model/Cache/Wallet.h"
#include "Money2/Model/Cache/Event.h"
#include "Money2/Model/Cache/SubscriptionStatus.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserAccessTokenDomain::FVerifyReceiptTask::FVerifyReceiptTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FVerifyReceiptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FVerifyReceiptTask::FVerifyReceiptTask(
        const FVerifyReceiptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FVerifyReceiptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FEventAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->VerifyReceipt(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Money2::Model::Cache::FEventCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetTransactionId(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FEventAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetTransactionId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FVerifyReceiptTask>> FUserAccessTokenDomain::VerifyReceipt(
        Request::FVerifyReceiptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyReceiptTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FAllocateSubscriptionStatusTask::FAllocateSubscriptionStatusTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FAllocateSubscriptionStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FAllocateSubscriptionStatusTask::FAllocateSubscriptionStatusTask(
        const FAllocateSubscriptionStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FAllocateSubscriptionStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->AllocateSubscriptionStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Money2::Model::Cache::FSubscriptionStatusCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetContentName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetContentName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FAllocateSubscriptionStatusTask>> FUserAccessTokenDomain::AllocateSubscriptionStatus(
        Request::FAllocateSubscriptionStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAllocateSubscriptionStatusTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FTakeoverSubscriptionStatusTask::FTakeoverSubscriptionStatusTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FTakeoverSubscriptionStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FTakeoverSubscriptionStatusTask::FTakeoverSubscriptionStatusTask(
        const FTakeoverSubscriptionStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FTakeoverSubscriptionStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->TakeoverSubscriptionStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Money2::Model::Cache::FSubscriptionStatusCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetContentName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetContentName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FTakeoverSubscriptionStatusTask>> FUserAccessTokenDomain::TakeoverSubscriptionStatus(
        Request::FTakeoverSubscriptionStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FTakeoverSubscriptionStatusTask>>(this->AsShared(), Request);
    }

    Gs2::Money2::Domain::Iterator::FDescribeWalletsIteratorPtr FUserAccessTokenDomain::Wallets(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeWalletsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeWallets(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FWallet::TypeName,
            Gs2::Money2::Model::Cache::FWalletCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeWallets(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FWallet::TypeName,
            Gs2::Money2::Model::Cache::FWalletCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectWalletsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FWalletPtr>>, public TSharedFromThis<FCollectWalletsTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FWalletPtr>)> OnCollected;

    public:
        explicit FCollectWalletsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FWalletPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectWalletsTask(const FCollectWalletsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FWalletPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FWalletPtr> Items;
            auto Iterator = Self->Wallets()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FWalletPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeWallets(
        TFunction<void(TArray<Gs2::Money2::Model::FWalletPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Money2::Model::Cache::FWalletCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FWallet::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FWalletPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FWallet>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectWalletsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateWallets()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FWallet::TypeName,
            Gs2::Money2::Model::Cache::FWalletCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeWalletsWithInitialCallTask::FSubscribeWalletsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FWalletPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeWalletsWithInitialCallTask::FSubscribeWalletsWithInitialCallTask(const FSubscribeWalletsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeWalletsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectWalletsTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FWalletPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeWallets(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeWalletsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeWalletsWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FWalletPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWalletsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FWalletAccessTokenDomain> FUserAccessTokenDomain::Wallet(
        const int32 Slot
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FWalletAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            Slot
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FEventAccessTokenDomain> FUserAccessTokenDomain::Event(
        const FString TransactionId
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FEventAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            TransactionId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TransactionId)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeSubscriptionStatusesIteratorPtr FUserAccessTokenDomain::SubscriptionStatuses(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeSubscriptionStatusesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSubscriptionStatuses(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FSubscriptionStatus::TypeName,
            Gs2::Money2::Model::Cache::FSubscriptionStatusCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeSubscriptionStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FSubscriptionStatus::TypeName,
            Gs2::Money2::Model::Cache::FSubscriptionStatusCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectSubscriptionStatusesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>>, public TSharedFromThis<FCollectSubscriptionStatusesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>)> OnCollected;

    public:
        explicit FCollectSubscriptionStatusesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectSubscriptionStatusesTask(const FCollectSubscriptionStatusesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FSubscriptionStatusPtr> Items;
            auto Iterator = Self->SubscriptionStatuses()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSubscriptionStatuses(
        TFunction<void(TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Money2::Model::Cache::FSubscriptionStatusCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FSubscriptionStatus::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FSubscriptionStatusPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FSubscriptionStatus>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscriptionStatusesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateSubscriptionStatuses()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FSubscriptionStatus::TypeName,
            Gs2::Money2::Model::Cache::FSubscriptionStatusCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeSubscriptionStatusesWithInitialCallTask::FSubscribeSubscriptionStatusesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeSubscriptionStatusesWithInitialCallTask::FSubscribeSubscriptionStatusesWithInitialCallTask(const FSubscribeSubscriptionStatusesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeSubscriptionStatusesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscriptionStatusesTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSubscriptionStatuses(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeSubscriptionStatusesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeSubscriptionStatusesWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FSubscriptionStatusPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSubscriptionStatusesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain> FUserAccessTokenDomain::SubscriptionStatus(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FSubscriptionStatusAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
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
