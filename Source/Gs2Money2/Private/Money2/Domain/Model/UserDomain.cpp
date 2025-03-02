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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserDomain::FVerifyReceiptTask::FVerifyReceiptTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FVerifyReceiptByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FVerifyReceiptTask::FVerifyReceiptTask(
        const FVerifyReceiptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FVerifyReceiptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FEventDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->VerifyReceiptByUserId(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Event"
                );
                const auto Key = Gs2::Money2::Domain::Model::FEventDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTransactionId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FEvent::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FEventDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetTransactionId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FVerifyReceiptTask>> FUserDomain::VerifyReceipt(
        Request::FVerifyReceiptByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyReceiptTask>>(this->AsShared(), Request);
    }

    FUserDomain::FAllocateSubscriptionStatusTask::FAllocateSubscriptionStatusTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FAllocateSubscriptionStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FAllocateSubscriptionStatusTask::FAllocateSubscriptionStatusTask(
        const FAllocateSubscriptionStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FAllocateSubscriptionStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AllocateSubscriptionStatusByUserId(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "SubscriptionStatus"
                );
                const auto Key = Gs2::Money2::Domain::Model::FSubscriptionStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetContentName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FSubscriptionStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FSubscriptionStatusDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetContentName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FAllocateSubscriptionStatusTask>> FUserDomain::AllocateSubscriptionStatus(
        Request::FAllocateSubscriptionStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAllocateSubscriptionStatusTask>>(this->AsShared(), Request);
    }

    FUserDomain::FTakeoverSubscriptionStatusTask::FTakeoverSubscriptionStatusTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FTakeoverSubscriptionStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FTakeoverSubscriptionStatusTask::FTakeoverSubscriptionStatusTask(
        const FTakeoverSubscriptionStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FTakeoverSubscriptionStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->TakeoverSubscriptionStatusByUserId(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "SubscriptionStatus"
                );
                const auto Key = Gs2::Money2::Domain::Model::FSubscriptionStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetContentName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FSubscriptionStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FSubscriptionStatusDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetContentName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FTakeoverSubscriptionStatusTask>> FUserDomain::TakeoverSubscriptionStatus(
        Request::FTakeoverSubscriptionStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FTakeoverSubscriptionStatusTask>>(this->AsShared(), Request);
    }

    Gs2::Money2::Domain::Iterator::FDescribeWalletsByUserIdIteratorPtr FUserDomain::Wallets(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeWalletsByUserIdIterator>(
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
            Gs2::Money2::Model::FWallet::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
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
            Gs2::Money2::Model::FWallet::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Wallet"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FWalletDomain> FUserDomain::Wallet(
        const int32 Slot
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FWalletDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            Slot
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeEventsByUserIdIteratorPtr FUserDomain::Events(
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeEventsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            Begin,
            End,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeEvents(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FEvent::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Event"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeEvents(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FEvent::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Event"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FEventDomain> FUserDomain::Event(
        const FString TransactionId
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FEventDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            TransactionId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TransactionId)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeSubscriptionStatusesByUserIdIteratorPtr FUserDomain::SubscriptionStatuses(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeSubscriptionStatusesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscriptionStatuses(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FSubscriptionStatus::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "SubscriptionStatus"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeSubscriptionStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FSubscriptionStatus::TypeName,
            Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "SubscriptionStatus"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FSubscriptionStatusDomain> FUserDomain::SubscriptionStatus(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FSubscriptionStatusDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
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

