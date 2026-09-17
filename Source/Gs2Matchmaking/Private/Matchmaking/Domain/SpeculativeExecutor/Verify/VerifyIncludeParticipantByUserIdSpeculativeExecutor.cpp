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

#include "Matchmaking/Domain/SpeculativeExecutor/Verify/VerifyIncludeParticipantByUserIdSpeculativeExecutor.h"
#include "Matchmaking/Model/Cache/SeasonGathering.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
namespace Gs2::Matchmaking::Domain::SpeculativeExecutor
{
namespace
{
    bool MembershipVerifyParticipantPredicate(
        const Gs2::Matchmaking::Model::FSeasonGatheringPtr& Item,
        const FString& ExpectedId,
        const FString& SeasonName,
        const int64 Season,
        const int64 Tier,
        const FString& GatheringName,
        const FString& RequestUserId,
        const FString& VerifyType
    )
    {
        if (!Item.IsValid() || !Item->GetSeasonGatheringId().IsSet() || Item->GetSeasonGatheringId().Get(FString()) != ExpectedId ||
            !Item->GetSeasonName().IsSet() || Item->GetSeasonName().Get(FString()) != SeasonName ||
            !Item->GetSeason().IsSet() || Item->GetSeason().Get(0) != Season ||
            !Item->GetTier().IsSet() || Item->GetTier().Get(0) != Tier ||
            !Item->GetName().IsSet() || Item->GetName().Get(FString()) != GatheringName ||
            !Item->GetParticipants().IsValid()) return false;
        const bool Included = Item->GetParticipants()->Contains(RequestUserId);
        if (VerifyType == TEXT("include")) return Included;
        if (VerifyType == TEXT("notInclude")) return !Included;
        return false;
    }
}
    FString FVerifyIncludeParticipantByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Matchmaking:VerifyIncludeParticipantByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyIncludeParticipantByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request,
        Gs2::Matchmaking::Model::FSeasonGatheringPtr Item
    )
    {
        if (Item.IsValid() && Item->GetParticipants().IsValid() && Request->GetUserId().IsSet())
        {
            const bool Included = Item->GetParticipants()->Contains(Request->GetUserId().Get(FString()));
            const auto Type = Request->GetVerifyType().Get(FString());
            if ((Type == TEXT("include") && Included) || (Type == TEXT("notInclude") && !Included)) return nullptr;
        }
        return MakeShared<Gs2::Core::Model::FBadRequestError>([]
        {
            auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("userId", "invalid", ""));
            return Arr;
        }());
    }

    FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request
    ):
        Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
    {

    }

    FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
        Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequest>(*Request);
        if (!PreparedRequest.IsValid() || !PreparedRequest->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("include") && VerifyType != TEXT("notInclude")) return nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetSeasonName().IsSet() || PreparedRequest->GetSeasonName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetSeasonGatheringName().IsSet() || PreparedRequest->GetSeasonGatheringName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetSeason().IsSet() || !PreparedRequest->GetTier().IsSet() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString());
        const FString TokenUserId = PreparedToken->GetUserId().Get(FString());
        const FString SeasonName = PreparedRequest->GetSeasonName().Get(FString());
        const int64 Season = PreparedRequest->GetSeason().Get(0);
        const int64 Tier = PreparedRequest->GetTier().Get(0);
        const FString GatheringName = PreparedRequest->GetSeasonGatheringName().Get(FString());
        const FString RequestUserId = PreparedRequest->GetUserId().Get(FString());
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:matchmaking:%s:season:%s:%lld:%lld:gathering:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *SeasonName, Season, Tier, *GatheringName);
        Gs2::Matchmaking::Model::FSeasonGatheringPtr Cached;
        if (!Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::TryGet(Domain->Cache, NamespaceName, TokenUserId, SeasonName, Season, Tier, GatheringName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetSeasonGatheringId().IsSet() || Cached->GetSeasonGatheringId().Get(FString()) != ExpectedId ||
            !Cached->GetSeasonName().IsSet() || Cached->GetSeasonName().Get(FString()) != SeasonName ||
            !Cached->GetSeason().IsSet() || Cached->GetSeason().Get(0) != Season ||
            !Cached->GetTier().IsSet() || Cached->GetTier().Get(0) != Tier ||
            !Cached->GetName().IsSet() || Cached->GetName().Get(FString()) != GatheringName ||
            !Cached->GetParticipants().IsValid()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, TokenUserId, SeasonName, Season, Tier, GatheringName, TimeOffset, ExpectedId, RequestUserId, VerifyType]()
        {
            Gs2::Matchmaking::Model::FSeasonGatheringPtr Current;
            if (!Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::TryGet(Cache, NamespaceName, TokenUserId, SeasonName, Season, Tier, GatheringName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return MembershipVerifyParticipantPredicate(Current, ExpectedId, SeasonName, Season, Tier, GatheringName, RequestUserId, VerifyType);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([]() {}), Guard);
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

    TSharedPtr<FAsyncTask<FVerifyIncludeParticipantByUserIdSpeculativeExecutor::FCommitTask>> FVerifyIncludeParticipantByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Matchmaking::Request::FVerifyIncludeParticipantByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("include")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notInclude")));
        else if (*Inverse->GetVerifyType() == TEXT("notInclude")) Inverse->WithVerifyType(TOptional<FString>(TEXT("include")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
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
