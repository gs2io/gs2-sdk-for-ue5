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

#include "Money2/Domain/Model/WalletAccessToken.h"
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

    FWalletAccessTokenDomain::FWalletAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<int32> Slot
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        Slot(Slot),
        ParentKey(Gs2::Money2::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Wallet"
        ))
    {
    }

    FWalletAccessTokenDomain::FWalletAccessTokenDomain(
        const FWalletAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        Slot(From.Slot),
        ParentKey(From.ParentKey)
    {

    }

    FWalletAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FWalletAccessTokenDomain>& Self,
        const Request::FGetWalletRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FWalletAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWalletAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FWallet>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSlot(Self->Slot);
        const auto Future = Self->Client->GetWallet(
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
                    Self->UserId(),
                    "Wallet"
                );
                const auto Key = Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetSlot().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSlot()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FWallet::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWalletAccessTokenDomain::FGetTask>> FWalletAccessTokenDomain::Get(
        Request::FGetWalletRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FWalletAccessTokenDomain::FWithdrawTask::FWithdrawTask(
        const TSharedPtr<FWalletAccessTokenDomain>& Self,
        const Request::FWithdrawRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FWalletAccessTokenDomain::FWithdrawTask::FWithdrawTask(
        const FWithdrawTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWalletAccessTokenDomain::FWithdrawTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FWalletAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSlot(Self->Slot);
        const auto Future = Self->Client->Withdraw(
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
                    Self->UserId(),
                    "Wallet"
                );
                const auto Key = Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetSlot().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSlot()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FWallet::TypeName,
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

    TSharedPtr<FAsyncTask<FWalletAccessTokenDomain::FWithdrawTask>> FWalletAccessTokenDomain::Withdraw(
        Request::FWithdrawRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FWithdrawTask>>(this->AsShared(), Request);
    }

    FString FWalletAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> Slot,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Slot.IsSet() ? *Slot : "null") + ":" +
            ChildType;
    }

    FString FWalletAccessTokenDomain::CreateCacheKey(
        TOptional<FString> Slot
    )
    {
        return FString("") +
            (Slot.IsSet() ? *Slot : "null");
    }

    FWalletAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FWalletAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FWalletAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FWalletAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FWallet>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FWallet> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FWallet>(
            Self->ParentKey,
            Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                Self->Slot.IsSet() ? FString::FromInt(*Self->Slot) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetWalletRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                    Self->Slot.IsSet() ? FString::FromInt(*Self->Slot) : TOptional<FString>()
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
                    Self->Slot.IsSet() ? FString::FromInt(*Self->Slot) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWalletAccessTokenDomain::FModelTask>> FWalletAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FWalletAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FWalletAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FWalletPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FWallet::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                Slot.IsSet() ? FString::FromInt(*Slot) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FWallet>(obj));
            }
        );
    }

    void FWalletAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FWallet::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FWalletDomain::CreateCacheKey(
                Slot.IsSet() ? FString::FromInt(*Slot) : TOptional<FString>()
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

