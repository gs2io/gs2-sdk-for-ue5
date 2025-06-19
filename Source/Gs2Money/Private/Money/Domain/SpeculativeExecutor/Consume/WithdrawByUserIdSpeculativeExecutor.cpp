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

#include "Money/Domain/SpeculativeExecutor/Consume/WithdrawByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Money/Domain/Gs2Money.h"

namespace Gs2::Money::Domain::SpeculativeExecutor
{

    FString FWithdrawByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Money:WithdrawByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FWithdrawByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request,
        Gs2::Money::Model::FWalletPtr Item
    )
    {
        if (*Request->GetPaidOnly()) {
            Item->WithPaid(*Item->GetPaid() - *Request->GetCount());
            if (*Item->GetPaid() < 0) {
                return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                {
                    auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                    return Arr;
                }());
            }
        }
        else {
            if (*Item->GetFree() + *Item->GetPaid() < *Request->GetCount()) {
                if (*Item->GetFree() < 0) {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                        return Arr;
                    }());
                }
            }
            else {
                Item->WithFree(*Item->GetFree() - *Request->GetCount());
                if (*Item->GetFree() < 0) {
                    Item->WithPaid(*Item->GetPaid() + *Item->GetFree());
                    Item->WithFree(0);
                }
            }
        }
        return nullptr;
    }

    FWithdrawByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FWithdrawByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FWithdrawByUserIdSpeculativeExecutor::FCommitTask::Action(
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
            Request->GetSlot()
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

    TSharedPtr<FAsyncTask<FWithdrawByUserIdSpeculativeExecutor::FCommitTask>> FWithdrawByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Money::Domain::FGs2MoneyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Money::Request::FWithdrawByUserIdRequestPtr FWithdrawByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetCount().IsSet())
        {
            Request->WithCount(*Request->GetCount() * Rate);
        }
        return Request;
    }

    Gs2::Money::Request::FWithdrawByUserIdRequestPtr FWithdrawByUserIdSpeculativeExecutor::Rate(
        const Gs2::Money::Request::FWithdrawByUserIdRequestPtr& Request,
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
