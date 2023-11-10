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

#include "Showcase/Domain/SpeculativeExecutor/Transaction/BuyByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Showcase::Domain::Transaction::SpeculativeExecutor
{
    FString FBuyByUserIdSpeculativeExecutor::Action() {
        return "Gs2Showcase:BuyByUserId";
    }

    FBuyByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FBuyByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FBuyByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBuyByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result)
    {
        const auto Future = Domain->Showcase->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : ""
            )->AccessToken(
                AccessToken
            )->Showcase(
                Request->GetShowcaseName().IsSet() ? *Request->GetShowcaseName() : ""
            )->DisplayItem(
                Request->GetDisplayItemId().IsSet() ? *Request->GetDisplayItemId() : ""
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();

        if (!Item.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([]{});
            return nullptr;
        }

        Service->OnIssueTransaction.Broadcast(
            MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                AccessToken,
                Item->GetSalesItem()->GetConsumeActions(),
                Item->GetSalesItem()->GetAcquireActions(),
                Request->GetQuantity().IsSet() ? *Request->GetQuantity() : 1.0
            )
        );

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBuyByUserIdSpeculativeExecutor::FCommitTask>> FBuyByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FBuyByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
