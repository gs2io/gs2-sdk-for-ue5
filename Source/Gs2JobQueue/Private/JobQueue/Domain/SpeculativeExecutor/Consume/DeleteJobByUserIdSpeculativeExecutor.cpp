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

#include "JobQueue/Domain/SpeculativeExecutor/Consume/DeleteJobByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::JobQueue::Domain::SpeculativeExecutor
{

    FString FDeleteJobByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2JobQueue:DeleteJobByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteJobByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request,
        Gs2::JobQueue::Model::FJobPtr Item
    )
    {
        return nullptr;
    }

    FDeleteJobByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteJobByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteJobByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto ParentKey = Model::FUserDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            FString("Job")
        );
        const auto Key = Model::FJobDomain::CreateCacheKey(
            Request->GetJobName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                JobQueue::Model::FJob::TypeName,
                ParentKey,
                Key,
                nullptr,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteJobByUserIdSpeculativeExecutor::FCommitTask>> FDeleteJobByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr FDeleteJobByUserIdSpeculativeExecutor::Rate(
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr FDeleteJobByUserIdSpeculativeExecutor::Rate(
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
