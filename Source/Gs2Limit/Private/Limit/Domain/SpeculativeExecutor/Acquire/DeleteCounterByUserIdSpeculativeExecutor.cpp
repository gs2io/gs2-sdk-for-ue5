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

#include "Limit/Domain/SpeculativeExecutor/Acquire/DeleteCounterByUserIdSpeculativeExecutor.h"
#include "Limit/Domain/Gs2Limit.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Limit::Domain::SpeculativeExecutor
{

    FString FDeleteCounterByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Limit:DeleteCounterByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteCounterByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request,
        Gs2::Limit::Model::FCounterPtr Item
    )
    {
        return nullptr;
    }

    FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto ParentKey = Model::FUserDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            FString("Counter")
        );
        const auto Key = Model::FCounterDomain::CreateCacheKey(
            Request->GetLimitName(),
            Request->GetCounterName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Limit::Model::FCounter::TypeName,
                ParentKey,
                Key,
                nullptr,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask>> FDeleteCounterByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr FDeleteCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr FDeleteCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
