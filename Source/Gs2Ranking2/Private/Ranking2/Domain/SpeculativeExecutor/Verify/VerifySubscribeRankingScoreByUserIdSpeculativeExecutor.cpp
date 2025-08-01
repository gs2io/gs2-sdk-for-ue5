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

#include "Ranking2/Domain/SpeculativeExecutor/Verify/VerifySubscribeRankingScoreByUserIdSpeculativeExecutor.h"
#include "Ranking2/Domain/Gs2Ranking2.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Ranking2::Domain::SpeculativeExecutor
{

    FString FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Ranking2:VerifySubscribeRankingScoreByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FVerifySubscribeRankingScoreByUserIdRequestPtr& Request,
        Gs2::Ranking2::Model::FSubscribeRankingScorePtr Item
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

    FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FVerifySubscribeRankingScoreByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Ranking2->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->User(
                AccessToken->GetUserId().IsSet() ? *AccessToken->GetUserId() : FString("")
            )->SubscribeRankingSeason(
                Request->GetRankingName().IsSet() ? *Request->GetRankingName() : FString(""),
                Request->GetSeason().IsSet() ? *Request->GetSeason() : 0
            )->SubscribeRankingScore()->Model();
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

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::FCommitTask>> FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FVerifySubscribeRankingScoreByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Ranking2::Request::FVerifySubscribeRankingScoreByUserIdRequestPtr FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::Rate(
        const Gs2::Ranking2::Request::FVerifySubscribeRankingScoreByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetScore().IsSet())
        {
            Request->WithScore(*Request->GetScore() * Rate);
        }
        return Request;
    }

    Gs2::Ranking2::Request::FVerifySubscribeRankingScoreByUserIdRequestPtr FVerifySubscribeRankingScoreByUserIdSpeculativeExecutor::Rate(
        const Gs2::Ranking2::Request::FVerifySubscribeRankingScoreByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetScore().IsSet())
        {
            Rate.Multiply(*Request->GetScore());
            Request->WithScore(Rate.ToInt());
        }
        return Request;
    }
}
