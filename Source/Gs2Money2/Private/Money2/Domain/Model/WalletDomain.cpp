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

#include "Money2/Domain/Model/Wallet.h"
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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FWalletDomain::FWalletDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<int32> Slot
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Slot(Slot),
        ParentKey(Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Wallet"
        ))
    {
    }

    FWalletDomain::FWalletDomain(
        const FWalletDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        Slot(From.Slot),
        ParentKey(From.ParentKey)
    {

    }

    FWalletDomain::FGetTask::FGetTask(
        const TSharedPtr<FWalletDomain>& Self,
        const Request::FGetWalletByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FWalletDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWalletDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FWallet>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithSlot(Self->Slot);
        const auto Future = Self->Client->GetWalletByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWalletDomain::FGetTask>> FWalletDomain::Get(
        Request::FGetWalletByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FWalletDomain::FDepositTask::FDepositTask(
        const TSharedPtr<FWalletDomain>& Self,
        const Request::FDepositByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FWalletDomain::FDepositTask::FDepositTask(
        const FDepositTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWalletDomain::FDepositTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FWalletDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithSlot(Self->Slot);
        const auto Future = Self->Client->DepositByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWalletDomain::FDepositTask>> FWalletDomain::Deposit(
        Request::FDepositByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDepositTask>>(this->AsShared(), Request);
    }

    FWalletDomain::FWithdrawTask::FWithdrawTask(
        const TSharedPtr<FWalletDomain>& Self,
        const Request::FWithdrawByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FWalletDomain::FWithdrawTask::FWithdrawTask(
        const FWithdrawTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWalletDomain::FWithdrawTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FWalletDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithSlot(Self->Slot);
        const auto Future = Self->Client->WithdrawByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWalletDomain::FWithdrawTask>> FWalletDomain::Withdraw(
        Request::FWithdrawByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FWithdrawTask>>(this->AsShared(), Request);
    }

    FString FWalletDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> Slot,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Slot.IsSet() ? FString::FromInt(*Slot) : "null") + ":" +
            ChildType;
    }

    FString FWalletDomain::CreateCacheKey(
        TOptional<int32> Slot
    )
    {
        return FString("") +
            (Slot.IsSet() ? FString::FromInt(*Slot) : "null");
    }

    FWalletDomain::FModelTask::FModelTask(
        const TSharedPtr<FWalletDomain> Self
    ): Self(Self)
    {

    }

    FWalletDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FWalletDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FWallet>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FWallet> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FWallet>(
            Self->ParentKey,
            Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                Self->Slot
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetWalletByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                    Self->Slot
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FWallet::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "wallet")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FWallet>(
                Self->ParentKey,
                Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                    Self->Slot
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWalletDomain::FModelTask>> FWalletDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FWalletDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FWalletDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FWalletPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FWallet::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                Slot
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FWallet>(obj));
            }
        );
    }

    void FWalletDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FWallet::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                Slot
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

