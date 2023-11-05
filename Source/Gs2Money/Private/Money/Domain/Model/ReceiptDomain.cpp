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

#include "Money/Domain/Model/Receipt.h"
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

    FReceiptDomain::FReceiptDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> TransactionId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Money::FGs2MoneyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        TransactionId(TransactionId),
        ParentKey(Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Receipt"
        ))
    {
    }

    FReceiptDomain::FReceiptDomain(
        const FReceiptDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        TransactionId(From.TransactionId),
        ParentKey(From.ParentKey)
    {

    }

    FReceiptDomain::FGetByUserIdAndTransactionIdTask::FGetByUserIdAndTransactionIdTask(
        const TSharedPtr<FReceiptDomain> Self,
        const Request::FGetByUserIdAndTransactionIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiptDomain::FGetByUserIdAndTransactionIdTask::FGetByUserIdAndTransactionIdTask(
        const FGetByUserIdAndTransactionIdTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiptDomain::FGetByUserIdAndTransactionIdTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FReceiptDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTransactionId(Self->TransactionId);
        const auto Future = Self->Client->GetByUserIdAndTransactionId(
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiptDomain::FGetByUserIdAndTransactionIdTask>> FReceiptDomain::GetByUserIdAndTransactionId(
        Request::FGetByUserIdAndTransactionIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetByUserIdAndTransactionIdTask>>(this->AsShared(), Request);
    }

    FString FReceiptDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TransactionId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TransactionId.IsSet() ? *TransactionId : "null") + ":" +
            ChildType;
    }

    FString FReceiptDomain::CreateCacheKey(
        TOptional<FString> TransactionId
    )
    {
        return FString("") +
            (TransactionId.IsSet() ? *TransactionId : "null");
    }

    FReceiptDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceiptDomain> Self
    ): Self(Self)
    {

    }

    FReceiptDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiptDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money::Model::FReceipt>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money::Model::FReceipt> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money::Model::FReceipt>(
            Self->ParentKey,
            Gs2::Money::Domain::Model::FReceiptDomain::CreateCacheKey(
                Self->TransactionId
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiptDomain::FModelTask>> FReceiptDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiptDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FReceiptDomain::Subscribe(
        TFunction<void(Gs2::Money::Model::FReceiptPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money::Model::FReceipt::TypeName,
            ParentKey,
            Gs2::Money::Domain::Model::FReceiptDomain::CreateCacheKey(
                TransactionId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money::Model::FReceipt>(obj));
            }
        );
    }

    void FReceiptDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money::Model::FReceipt::TypeName,
            ParentKey,
            Gs2::Money::Domain::Model::FReceiptDomain::CreateCacheKey(
                TransactionId
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

