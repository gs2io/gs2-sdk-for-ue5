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
#include "Matchmaking/Domain/Model/CurrentModelMaster.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"
#include "Matchmaking/Domain/Model/Season.h"
#include "Matchmaking/Domain/Model/SeasonAccessToken.h"
#include "Matchmaking/Domain/Model/SeasonModel.h"
#include "Matchmaking/Domain/Model/SeasonModelMaster.h"
#include "Matchmaking/Domain/Model/SeasonGathering.h"
#include "Matchmaking/Domain/Model/SeasonGatheringAccessToken.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGathering.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGatheringAccessToken.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Domain/Model/Vote.h"
#include "Matchmaking/Model/Cache/Vote.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FVoteDomain::FVoteDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RatingName,
        const TOptional<FString> GatheringName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RatingName(From.RatingName),
        GatheringName(From.GatheringName),
        ParentKey(From.ParentKey)
    {

    }

    FVoteDomain::FCommitTask::FCommitTask(
        const TSharedPtr<FVoteDomain>& Self,
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

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
        const auto CacheParentKey = Gs2::Matchmaking::Model::Cache::FVoteCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Matchmaking::Model::Cache::FVoteCache::CreateCacheKey(

            Self->RatingName,
            Self->GatheringName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Matchmaking::Model::FVote::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Matchmaking::Model::FVotePtr Value;
                const auto CacheHit = Gs2::Matchmaking::Model::Cache::FVoteCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RatingName,
                    Self->GatheringName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FVoteDomain::FModelTask>> FVoteDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FVoteDomain::FModelTask>>(this->AsShared());
    }

    void FVoteDomain::Invalidate()
    {
        Gs2::Matchmaking::Model::Cache::FVoteCache::Delete(
            Gs2->Cache,

            NamespaceName,
            RatingName,
            GatheringName,
            TOptional<int32>()
        );
    }

    FVoteDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FVoteDomain>& Self,
        TFunction<void(Gs2::Matchmaking::Model::FVotePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FVoteDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FVoteDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVoteDomain::FSubscribeWithInitialCallTask>> FVoteDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Matchmaking::Model::FVotePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FVoteDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FVotePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Matchmaking::Model::Cache::FVoteCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Matchmaking::Model::Cache::FVoteCache::CreateCacheKey(

            RatingName,
            GatheringName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRatingName = RatingName;
        const TOptional<FString> QueryGatheringName = GatheringName;
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FVote::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FVote>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRatingName, QueryGatheringName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FVoteDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryRatingName,
                    QueryGatheringName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FVoteDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Matchmaking::Model::Cache::FVoteCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Matchmaking::Model::Cache::FVoteCache::CreateCacheKey(

            RatingName,
            GatheringName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FVote::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
