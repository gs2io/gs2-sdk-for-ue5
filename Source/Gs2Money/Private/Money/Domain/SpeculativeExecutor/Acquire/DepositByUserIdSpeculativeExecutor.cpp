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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Money/Domain/SpeculativeExecutor/Acquire/DepositByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Money/Domain/Gs2Money.h"

namespace Gs2::Money::Domain::SpeculativeExecutor
{

    FString FDepositByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Money:DepositByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDepositByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request,
        Gs2::Money::Model::FWalletPtr Item
    )
    {
        if (*Request->GetPrice() > 0)
        {
            Item->WithPaid(*Item->GetPaid() + *Request->GetCount());
        } else
        {
            Item->WithFree(*Item->GetFree() + *Request->GetCount());
        }
        return nullptr;
    }

    FDepositByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDepositByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDepositByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Money->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Wallet(
                Request->GetSlot().IsSet() ? *Request->GetSlot() : 0
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        auto Item = Future->GetTask().Result();

        if (!Item.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([&]()
            {
                return nullptr;
            });
            return nullptr;
        }
        auto Err = Transform(Domain, AccessToken, Request, Item);
        if (Err != nullptr)
        {
            return Err;
        }

        const auto ParentKey = Model::FUserDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            FString("Wallet")
        );
        const auto Key = Model::FWalletDomain::CreateCacheKey(
            FString::FromInt(*Request->GetSlot())
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Money::Model::FWallet::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDepositByUserIdSpeculativeExecutor::FCommitTask>> FDepositByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Money::Request::FDepositByUserIdRequestPtr FDepositByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetCount().IsSet())
        {
            Request->WithCount(*Request->GetCount() * Rate);
        }
        return Request;
    }

    Gs2::Money::Request::FDepositByUserIdRequestPtr FDepositByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FDepositByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetCount().IsSet())
        {
            Rate.Multiply(*Request->GetCount());
            Request->WithCount(Rate.ToInt());
        }
        return Request;
    }
}
