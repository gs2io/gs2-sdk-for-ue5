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

#include "Enhance/Domain/SpeculativeExecutor/Acquire/DirectEnhanceByUserIdSpeculativeExecutor.h"
#include "Enhance/Domain/Gs2Enhance.h"
#include "Enhance/Domain/SpeculativeExecutor/Transaction/DirectEnhanceByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Enhance::Domain::SpeculativeExecutor
{

    FString FDirectEnhanceByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Enhance:DirectEnhanceByUserId");
    }

    FDirectEnhanceByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FDirectEnhanceByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDirectEnhanceByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDirectEnhanceByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Transaction::SpeculativeExecutor::FDirectEnhanceByUserIdSpeculativeExecutor::Execute(
            Domain,
            Service,
            AccessToken,
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Commit = Future->GetTask().Result();

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            if (Commit.IsValid())
            {
                (*Commit)();
            }
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDirectEnhanceByUserIdSpeculativeExecutor::FCommitTask>> FDirectEnhanceByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FDirectEnhanceByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Enhance::Request::FDirectEnhanceByUserIdRequestPtr FDirectEnhanceByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enhance::Request::FDirectEnhanceByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Enhance::Request::FDirectEnhanceByUserIdRequestPtr FDirectEnhanceByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enhance::Request::FDirectEnhanceByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
