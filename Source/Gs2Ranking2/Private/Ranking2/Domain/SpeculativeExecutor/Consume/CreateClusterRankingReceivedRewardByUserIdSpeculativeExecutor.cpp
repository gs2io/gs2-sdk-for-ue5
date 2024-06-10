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

#include "Ranking2/Domain/SpeculativeExecutor/Consume/CreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Ranking2::Domain::SpeculativeExecutor
{

    FString FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Ranking2:CreateClusterRankingReceivedRewardByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr& Request,
        Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr Item
    )
    {
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        *Result = MakeShared<TFunction<void()>>([&]()
        {
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::FCommitTask>> FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Ranking2::Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::Rate(
        const Gs2::Ranking2::Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Ranking2::Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr FCreateClusterRankingReceivedRewardByUserIdSpeculativeExecutor::Rate(
        const Gs2::Ranking2::Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
