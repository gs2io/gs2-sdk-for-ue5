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

#include "Matchmaking/Domain/Model/Vote.h"
#include "Matchmaking/Domain/Model/Namespace.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/GatheringAccessToken.h"
#include "Matchmaking/Domain/Model/RatingModelMaster.h"
#include "Matchmaking/Domain/Model/RatingModel.h"
#include "Matchmaking/Domain/Model/CurrentRatingModelMaster.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Domain/Model/Vote.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FVoteDomain::FVoteDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RatingName,
        const TOptional<FString> GatheringName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Session)),
        NamespaceName(NamespaceName),
        RatingName(RatingName),
        GatheringName(GatheringName),
        ParentKey(Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Vote"
        ))
    {
    }

    FVoteDomain::FVoteDomain(
        const FVoteDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RatingName(From.RatingName),
        GatheringName(From.GatheringName),
        ParentKey(From.ParentKey)
    {

    }

    FVoteDomain::FCommitTask::FCommitTask(
        const TSharedPtr<FVoteDomain> Self,
        const Request::FCommitVoteRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FVoteDomain::FCommitTask::FCommitTask(
        const FCommitTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FVoteDomain::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FVoteDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRatingName(Self->RatingName)
            ->WithGatheringName(Self->GatheringName);
        const auto Future = Self->Client->CommitVote(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVoteDomain::FCommitTask>> FVoteDomain::Commit(
        Request::FCommitVoteRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(this->AsShared(), Request);
    }

    FString FVoteDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RatingName,
        TOptional<FString> GatheringName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RatingName.IsSet() ? *RatingName : "null") + ":" +
            (GatheringName.IsSet() ? *GatheringName : "null") + ":" +
            ChildType;
    }

    FString FVoteDomain::CreateCacheKey(
        TOptional<FString> RatingName,
        TOptional<FString> GatheringName
    )
    {
        return FString("") +
            (RatingName.IsSet() ? *RatingName : "null") + ":" + 
            (GatheringName.IsSet() ? *GatheringName : "null");
    }

    FVoteDomain::FModelTask::FModelTask(
        const TSharedPtr<FVoteDomain> Self
    ): Self(Self)
    {

    }

    FVoteDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVoteDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FVote>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FVote> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Matchmaking::Model::FVote>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FVoteDomain::CreateCacheKey(
                Self->RatingName,
                Self->GatheringName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVoteDomain::FModelTask>> FVoteDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FVoteDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FVoteDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FVotePtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Matchmaking::Model::FVote::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FVoteDomain::CreateCacheKey(
                RatingName,
                GatheringName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FVote>(obj));
            }
        );
    }

    void FVoteDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FVote::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FVoteDomain::CreateCacheKey(
                RatingName,
                GatheringName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

