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

#include "Money/Domain/Model/User.h"
#include "Money/Domain/Model/Namespace.h"
#include "Money/Domain/Model/User.h"
#include "Money/Domain/Model/UserAccessToken.h"
#include "Money/Domain/Model/Wallet.h"
#include "Money/Domain/Model/WalletAccessToken.h"
#include "Money/Domain/Model/Receipt.h"
#include "Money/Domain/Model/ReceiptAccessToken.h"
#include "Money/Model/Cache/Wallet.h"
#include "Money/Model/Cache/Receipt.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money::Domain::FGs2MoneyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money::FGs2MoneyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Money::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserDomain::FRecordReceiptTask::FRecordReceiptTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FRecordReceiptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FRecordReceiptTask::FRecordReceiptTask(
        const FRecordReceiptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FRecordReceiptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RecordReceipt(
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
              }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Money::Model::Cache::FReceiptCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetTransactionId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Money::Domain::Model::FReceiptDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetTransactionId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FRecordReceiptTask>> FUserDomain::RecordReceipt(
        Request::FRecordReceiptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRecordReceiptTask>>(this->AsShared(), Request);
    }

    FUserDomain::FRevertRecordReceiptTask::FRevertRecordReceiptTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FRevertRecordReceiptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FRevertRecordReceiptTask::FRevertRecordReceiptTask(
        const FRevertRecordReceiptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FRevertRecordReceiptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RevertRecordReceipt(
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
              }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Money::Model::Cache::FReceiptCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetTransactionId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Money::Domain::Model::FReceiptDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetTransactionId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FRevertRecordReceiptTask>> FUserDomain::RevertRecordReceipt(
        Request::FRevertRecordReceiptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRevertRecordReceiptTask>>(this->AsShared(), Request);
    }

    Gs2::Money::Domain::Iterator::FDescribeWalletsByUserIdIteratorPtr FUserDomain::Wallets(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Money::Domain::Iterator::FDescribeWalletsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeWallets(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money::Model::FWallet::TypeName,
            Gs2::Money::Model::Cache::FWalletCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeWallets(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money::Model::FWallet::TypeName,
            Gs2::Money::Model::Cache::FWalletCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectWalletsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money::Model::FWalletPtr>>, public TSharedFromThis<FCollectWalletsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Money::Model::FWalletPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectWalletsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Money::Model::FWalletPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectWalletsTask(const FCollectWalletsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money::Model::FWalletPtr>>> Result) override
        {
            TArray<Gs2::Money::Model::FWalletPtr> Items;
            auto Iterator = Self->Wallets(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money::Model::FWalletPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeWallets(
        TFunction<void(TArray<Gs2::Money::Model::FWalletPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money::Domain::FGs2MoneyDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Money::Model::Cache::FWalletCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money::Model::FWallet::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money::Model::FWalletPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money::Model::FWallet>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectWalletsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateWallets(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money::Model::FWallet::TypeName,
            Gs2::Money::Model::Cache::FWalletCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeWalletsWithInitialCallTask::FSubscribeWalletsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Money::Model::FWalletPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeWalletsWithInitialCallTask::FSubscribeWalletsWithInitialCallTask(const FSubscribeWalletsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeWalletsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectWalletsTask>>(Self, TFunction<void(TArray<Gs2::Money::Model::FWalletPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeWallets(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeWalletsWithInitialCallTask>> FUserDomain::SubscribeWalletsWithInitialCall(TFunction<void(TArray<Gs2::Money::Model::FWalletPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWalletsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Money::Domain::Model::FWalletDomain> FUserDomain::Wallet(
        const int32 Slot
    )
    {
        return MakeShared<Gs2::Money::Domain::Model::FWalletDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            Slot
        );
    }

    Gs2::Money::Domain::Iterator::FDescribeReceiptsIteratorPtr FUserDomain::Receipts(
        const TOptional<int32> Slot,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Money::Domain::Iterator::FDescribeReceiptsIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            Slot,
            Begin,
            End,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeReceipts(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money::Model::FReceipt::TypeName,
            Gs2::Money::Model::Cache::FReceiptCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeReceipts(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money::Model::FReceipt::TypeName,
            Gs2::Money::Model::Cache::FReceiptCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectReceiptsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money::Model::FReceiptPtr>>, public TSharedFromThis<FCollectReceiptsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Money::Model::FReceiptPtr>)> OnCollected;
    const TOptional<int32> QuerySlot;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectReceiptsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Money::Model::FReceiptPtr>)> OnCollected,const TOptional<int32> Slot,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QuerySlot(Slot), QueryBegin(Begin), QueryEnd(End), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectReceiptsTask(const FCollectReceiptsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QuerySlot(From.QuerySlot), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money::Model::FReceiptPtr>>> Result) override
        {
            TArray<Gs2::Money::Model::FReceiptPtr> Items;
            auto Iterator = Self->Receipts(QuerySlot, QueryBegin, QueryEnd, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money::Model::FReceiptPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeReceipts(
        TFunction<void(TArray<Gs2::Money::Model::FReceiptPtr>)> Callback,const TOptional<int32> Slot,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money::Domain::FGs2MoneyDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QuerySlot = Slot;
        const auto QueryBegin = Begin;
        const auto QueryEnd = End;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Money::Model::Cache::FReceiptCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money::Model::FReceipt::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money::Model::FReceiptPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money::Model::FReceipt>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QuerySlot, QueryBegin, QueryEnd, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiptsTask>>(Domain, Callback, QuerySlot, QueryBegin, QueryEnd, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateReceipts(const TOptional<int32> Slot,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money::Model::FReceipt::TypeName,
            Gs2::Money::Model::Cache::FReceiptCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeReceiptsWithInitialCallTask::FSubscribeReceiptsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Money::Model::FReceiptPtr>)> Callback,const TOptional<int32> Slot,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QuerySlot(Slot), QueryBegin(Begin), QueryEnd(End), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeReceiptsWithInitialCallTask::FSubscribeReceiptsWithInitialCallTask(const FSubscribeReceiptsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QuerySlot(From.QuerySlot), QueryBegin(From.QueryBegin), QueryEnd(From.QueryEnd), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeReceiptsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiptsTask>>(Self, TFunction<void(TArray<Gs2::Money::Model::FReceiptPtr>)>(), QuerySlot, QueryBegin, QueryEnd, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeReceipts(Callback, QuerySlot, QueryBegin, QueryEnd, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeReceiptsWithInitialCallTask>> FUserDomain::SubscribeReceiptsWithInitialCall(TFunction<void(TArray<Gs2::Money::Model::FReceiptPtr>)> Callback,const TOptional<int32> Slot,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeReceiptsWithInitialCallTask>>(this->AsShared(), Callback, Slot, Begin, End, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain> FUserDomain::Receipt(
        const FString TransactionId
    )
    {
        return MakeShared<Gs2::Money::Domain::Model::FReceiptDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            TransactionId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TransactionId)
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
