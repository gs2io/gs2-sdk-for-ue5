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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Wallet"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeWallets(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FWallet::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Wallet"
            ),
            CallbackID
        );
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
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "SubscriptionStatus"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeSubscriptionStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FSubscriptionStatus::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "SubscriptionStatus"
            ),
            CallbackID
        );
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

