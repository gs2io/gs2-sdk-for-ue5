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

#include "Matchmaking/Domain/SpeculativeExecutor/Consume/VerifyIncludeParticipantByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Matchmaking::Domain::SpeculativeExecutor
{

    FString FVerifyIncludeParticipantByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Matchmaking:VerifyIncludeParticipantByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyIncludeParticipantByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request,
        Gs2::Matchmaking::Model::FSeasonGatheringPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        if (Request->GetVerifyType().IsSet()) {
            if (*Request->GetVerifyType() == "include")
            {
            } else if (*Request->GetVerifyType() == "notInclude")
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

    FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Matchmaking->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Season(
                Request->GetSeasonName().IsSet() ? *Request->GetSeasonName() : FString(""),
                Request->GetSeason().IsSet() ? *Request->GetSeason() : FString("")
            )->SeasonGathering(
                Request->GetTier().IsSet() ? *Request->GetTier() : FString(""),
                Request->GetSeasonGatheringName().IsSet() ? *Request->GetSeasonGatheringName() : FString("")
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

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask>> FVerifyIncludeParticipantByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr FVerifyIncludeParticipantByUserIdSpeculativeExecutor::Rate(
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr FVerifyIncludeParticipantByUserIdSpeculativeExecutor::Rate(
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
