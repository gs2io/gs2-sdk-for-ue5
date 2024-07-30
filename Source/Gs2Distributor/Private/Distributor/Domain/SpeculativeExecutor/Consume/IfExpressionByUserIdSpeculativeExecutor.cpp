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

#include "Distributor/Domain/SpeculativeExecutor/Consume/IfExpressionByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Distributor::Domain::SpeculativeExecutor
{

    FString FIfExpressionByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Distributor:IfExpressionByUserId");
    }

    FIfExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FIfExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIfExpressionByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr("Gs2Distributor:IfExpressionByUserId"))
        
        *Result = MakeShared<TFunction<void()>>([&]()
        {
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIfExpressionByUserIdSpeculativeExecutor::FCommitTask>> FIfExpressionByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr FIfExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr FIfExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
