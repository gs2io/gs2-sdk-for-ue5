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

#include "Experience/Domain/SpeculativeExecutor/Transaction/MultiplyAcquireActionsByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Experience::Domain::Transaction::SpeculativeExecutor
{
    FString FMultiplyAcquireActionsByUserIdSpeculativeExecutor::Action() {
        return "Gs2Experience:MultiplyAcquireActionsByUserId";
    }

    FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FMultiplyAcquireActionsByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result)
    {
        const auto Future = Domain->Experience->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : ""
            )->AccessToken(
                AccessToken
            )->Status(
                Request->GetExperienceName().IsSet() ? *Request->GetExperienceName() : "",
                Request->GetPropertyId().IsSet() ? *Request->GetPropertyId() : ""
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

        const auto Future2 = Domain->Experience->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : ""
            )->ExperienceModel(
                Request->GetExperienceName().IsSet() ? *Request->GetExperienceName() : ""
            )->Model();
        Future2->StartSynchronousTask();
        if (Future2->GetTask().IsError())
        {
            return Future2->GetTask().Error();
        }
        const auto Model = Future2->GetTask().Result();

        if (!Model.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([]{});
            return nullptr;
        }

        const auto Rate = *Model->GetAcquireActionRates()->FindByPredicate([Model](Gs2::Experience::Model::FAcquireActionRatePtr V1)
        {
            return *V1->GetName() == *Model->GetName();
        });
        if (!Rate.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([]{});
            return nullptr;
        }
        TBigInt<1024, false> RateValue;
        if (*Rate->GetMode() == "double")
        {
            RateValue.Set((*Rate->GetRates())[static_cast<int>(*Item->GetRankValue())]);
        } else
        {
            RateValue.Parse((*Rate->GetBigRates())[static_cast<int>(*Item->GetRankValue())]);
        }
        
        Service->OnIssueTransaction.Broadcast(
            MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                AccessToken,
                MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>(),
                Request->GetAcquireActions(),
                RateValue
            )
        );

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask>> FMultiplyAcquireActionsByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FMultiplyAcquireActionsByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
