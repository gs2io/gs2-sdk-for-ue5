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

#include "AdReward/Domain/SpeculativeExecutor/Verify/VerifyPointByUserIdSpeculativeExecutor.h"
#include "AdReward/Domain/Gs2AdReward.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::AdReward::Domain::SpeculativeExecutor
{

    FString FVerifyPointByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2AdReward:VerifyPointByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyPointByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FVerifyPointByUserIdRequestPtr& Request,
        Gs2::AdReward::Model::FPointPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        if (Request->GetVerifyType().IsSet()) {
            if (*Request->GetVerifyType() == "less")
            {
            } else if (*Request->GetVerifyType() == "lessEqual")
            {
            } else if (*Request->GetVerifyType() == "greater")
            {
            } else if (*Request->GetVerifyType() == "greaterEqual")
            {
            } else if (*Request->GetVerifyType() == "equal")
            {
            } else if (*Request->GetVerifyType() == "notEqual")
            {
            } else {
                return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                {
                    auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("verifyType", "invalid", ""));
                    return Arr;
                }());
            }
        }
        return nullptr;
    }

    FVerifyPointByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FVerifyPointByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyPointByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyPointByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        const auto Future = Domain->AdReward->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Point(
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        auto Item = Future->GetTask().Result();

        if (!Item.IsValid())
        {
            *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([]()
            {
                return nullptr;
            }));
            return nullptr;
        }
        auto Err = Transform(Domain, AccessToken, Request, Item);
        if (Err != nullptr)
        {
            return Err;
        }

        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([]()
        {
            return nullptr;
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyPointByUserIdSpeculativeExecutor::FCommitTask>> FVerifyPointByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FVerifyPointByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::AdReward::Request::FVerifyPointByUserIdRequestPtr FVerifyPointByUserIdSpeculativeExecutor::Rate(
        const Gs2::AdReward::Request::FVerifyPointByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetPoint().IsSet())
        {
            Request->WithPoint(*Request->GetPoint() * Rate);
        }
        return Request;
    }

    Gs2::AdReward::Request::FVerifyPointByUserIdRequestPtr FVerifyPointByUserIdSpeculativeExecutor::Rate(
        const Gs2::AdReward::Request::FVerifyPointByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetPoint().IsSet())
        {
            Rate.Multiply(*Request->GetPoint());
            Request->WithPoint(Rate.ToInt());
        }
        return Request;
    }
}
