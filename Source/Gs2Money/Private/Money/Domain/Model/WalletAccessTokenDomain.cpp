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

#include "Money/Domain/Model/WalletAccessToken.h"
#include "Money/Domain/Model/Wallet.h"
#include "Money/Domain/Model/Namespace.h"
#include "Money/Domain/Model/User.h"
#include "Money/Domain/Model/UserAccessToken.h"
#include "Money/Domain/Model/Wallet.h"
#include "Money/Domain/Model/WalletAccessToken.h"
#include "Money/Domain/Model/Receipt.h"
#include "Money/Domain/Model/ReceiptAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Money::Domain::Model
{

    FWalletAccessTokenDomain::FWalletAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<int32> Slot
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Money::FGs2MoneyRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        Slot(Slot),
        ParentKey(Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Wallet"
        ))
    {
    }

    FWalletAccessTokenDomain::FWalletAccessTokenDomain(
        const FWalletAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        Slot(From.Slot),
        ParentKey(From.ParentKey)
    {

    }

    FWalletAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FWalletAccessTokenDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Money::Model::FWallet>> Result
    )
    {
        Request
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
                const auto ParentKey = Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Wallet"
                );
                const auto Key = Gs2::Money::Domain::Model::FWalletDomain::CreateCacheKey(
                    TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Money::Model::FWallet::TypeName,
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
        const TSharedPtr<FWalletAccessTokenDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Money::Domain::Model::FWalletAccessTokenDomain>> Result
    )
    {
        Request
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
                const auto ParentKey = Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Wallet"
                );
                const auto Key = Gs2::Money::Domain::Model::FWalletDomain::CreateCacheKey(
                    TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Money::Model::FWallet::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Price = *ResultModel->GetPrice();

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
        TSharedPtr<TSharedPtr<Gs2::Money::Model::FWallet>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money::Model::FWallet> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Money::Model::FWallet>(
            Self->ParentKey,
            Gs2::Money::Domain::Model::FWalletDomain::CreateCacheKey(
                TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money::Request::FGetWalletRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money::Domain::Model::FWalletDomain::CreateCacheKey(
                    TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Money::Model::FWallet::TypeName,
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
            Self->Cache->TryGet<Gs2::Money::Model::FWallet>(
                Self->ParentKey,
                Gs2::Money::Domain::Model::FWalletDomain::CreateCacheKey(
                    TOptional<FString>()
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
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

