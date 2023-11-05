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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Money::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
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
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FRecordReceiptTask::FRecordReceiptTask(
        const TSharedPtr<FUserDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Receipt"
                );
                const auto Key = Gs2::Money::Domain::Model::FReceiptDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTransactionId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money::Model::FReceipt::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Money::Domain::Model::FReceiptDomain>(
            Self->Gs2,
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
        const TSharedPtr<FUserDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Receipt"
                );
                const auto Key = Gs2::Money::Domain::Model::FReceiptDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTransactionId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money::Model::FReceipt::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Money::Domain::Model::FReceiptDomain>(
            Self->Gs2,
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
    ) const
    {
        return MakeShared<Gs2::Money::Domain::Iterator::FDescribeWalletsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeWallets(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money::Model::FWallet::TypeName,
            Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Wallet"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeWallets(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money::Model::FWallet::TypeName,
            Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Wallet"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money::Domain::Model::FWalletDomain> FUserDomain::Wallet(
        const int32 Slot
    ) const
    {
        return MakeShared<Gs2::Money::Domain::Model::FWalletDomain>(
            Gs2,
            NamespaceName,
            UserId,
            Slot
        );
    }

    Gs2::Money::Domain::Iterator::FDescribeReceiptsIteratorPtr FUserDomain::Receipts(
        const TOptional<int32> Slot,
        const TOptional<int64> Begin,
        const TOptional<int64> End
    ) const
    {
        return MakeShared<Gs2::Money::Domain::Iterator::FDescribeReceiptsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            Slot,
            Begin,
            End
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeReceipts(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money::Model::FReceipt::TypeName,
            Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Receipt"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeReceipts(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money::Model::FReceipt::TypeName,
            Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Receipt"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain> FUserDomain::Receipt(
        const FString TransactionId
    ) const
    {
        return MakeShared<Gs2::Money::Domain::Model::FReceiptDomain>(
            Gs2,
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

