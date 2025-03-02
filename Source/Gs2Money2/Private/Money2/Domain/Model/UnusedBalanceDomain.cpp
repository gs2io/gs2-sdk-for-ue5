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

#include "Money2/Domain/Model/UnusedBalance.h"
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

    FUnusedBalanceDomain::FUnusedBalanceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> Currency
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Currency(Currency),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "UnusedBalance"
        ))
    {
    }

    FUnusedBalanceDomain::FUnusedBalanceDomain(
        const FUnusedBalanceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Currency(From.Currency),
        ParentKey(From.ParentKey)
    {

    }

    FUnusedBalanceDomain::FGetTask::FGetTask(
        const TSharedPtr<FUnusedBalanceDomain>& Self,
        const Request::FGetUnusedBalanceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUnusedBalanceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUnusedBalanceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FUnusedBalance>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCurrency(Self->Currency);
        const auto Future = Self->Client->GetUnusedBalance(
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
                const auto ParentKey = Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "UnusedBalance"
                );
                const auto Key = Gs2::Money2::Domain::Model::FUnusedBalanceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetCurrency()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FUnusedBalance::TypeName,
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

    TSharedPtr<FAsyncTask<FUnusedBalanceDomain::FGetTask>> FUnusedBalanceDomain::Get(
        Request::FGetUnusedBalanceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FUnusedBalanceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> Currency,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Currency.IsSet() ? *Currency : "null") + ":" +
            ChildType;
    }

    FString FUnusedBalanceDomain::CreateCacheKey(
        TOptional<FString> Currency
    )
    {
        return FString("") +
            (Currency.IsSet() ? *Currency : "null");
    }

    FUnusedBalanceDomain::FModelTask::FModelTask(
        const TSharedPtr<FUnusedBalanceDomain> Self
    ): Self(Self)
    {

    }

    FUnusedBalanceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FUnusedBalanceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FUnusedBalance>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Money2::Model::FUnusedBalance> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FUnusedBalance>(
            Self->ParentKey,
            Gs2::Money2::Domain::Model::FUnusedBalanceDomain::CreateCacheKey(
                Self->Currency
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Money2::Request::FGetUnusedBalanceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Money2::Domain::Model::FUnusedBalanceDomain::CreateCacheKey(
                    Self->Currency
                );
                Self->Gs2->Cache->Put(
                    Gs2::Money2::Model::FUnusedBalance::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "unusedBalance")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Money2::Model::FUnusedBalance>(
                Self->ParentKey,
                Gs2::Money2::Domain::Model::FUnusedBalanceDomain::CreateCacheKey(
                    Self->Currency
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUnusedBalanceDomain::FModelTask>> FUnusedBalanceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FUnusedBalanceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FUnusedBalanceDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FUnusedBalancePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FUnusedBalanceDomain::CreateCacheKey(
                Currency
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FUnusedBalance>(obj));
            }
        );
    }

    void FUnusedBalanceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            ParentKey,
            Gs2::Money2::Domain::Model::FUnusedBalanceDomain::CreateCacheKey(
                Currency
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

