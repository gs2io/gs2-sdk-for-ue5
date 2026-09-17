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

#include "SeasonRating/Domain/Model/Vote.h"
#include "SeasonRating/Domain/Model/Namespace.h"
#include "SeasonRating/Domain/Model/MatchSession.h"
#include "SeasonRating/Domain/Model/SeasonModelMaster.h"
#include "SeasonRating/Domain/Model/SeasonModel.h"
#include "SeasonRating/Domain/Model/CurrentSeasonModelMaster.h"
#include "SeasonRating/Domain/Model/Ballot.h"
#include "SeasonRating/Domain/Model/BallotAccessToken.h"
#include "SeasonRating/Domain/Model/Vote.h"
#include "SeasonRating/Domain/Model/User.h"
#include "SeasonRating/Domain/Model/UserAccessToken.h"
#include "SeasonRating/Model/Cache/Vote.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SeasonRating::Domain::Model
{

    FVoteDomain::FVoteDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SeasonRating::Domain::FGs2SeasonRatingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SeasonName,
        const TOptional<FString> SessionName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SeasonRating::FGs2SeasonRatingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        SeasonName(SeasonName),
        SessionName(SessionName),
        ParentKey(Gs2::SeasonRating::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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
        SeasonName(From.SeasonName),
        SessionName(From.SessionName),
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
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Domain::Model::FVoteDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName)
            ->WithSessionName(Self->SessionName);
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
        TOptional<FString> SeasonName,
        TOptional<FString> SessionName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            (SessionName.IsSet() ? *SessionName : "null") + ":" +
            ChildType;
    }

    FString FVoteDomain::CreateCacheKey(
        TOptional<FString> SeasonName,
        TOptional<FString> SessionName
    )
    {
        return FString("") +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            (SessionName.IsSet() ? *SessionName : "null");
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
        TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FVote>> Result
    )
    {
        const auto CacheParentKey = Gs2::SeasonRating::Model::Cache::FVoteCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::SeasonRating::Model::Cache::FVoteCache::CreateCacheKey(

            Self->SeasonName,
            Self->SessionName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SeasonRating::Model::FVote::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SeasonRating::Model::FVotePtr Value;
                const auto CacheHit = Gs2::SeasonRating::Model::Cache::FVoteCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->SeasonName,
                    Self->SessionName,
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
        Gs2::SeasonRating::Model::Cache::FVoteCache::Delete(
            Gs2->Cache,

            NamespaceName,
            SeasonName,
            SessionName,
            TOptional<int32>()
        );
    }

    FVoteDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FVoteDomain>& Self,
        TFunction<void(Gs2::SeasonRating::Model::FVotePtr)> Callback
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
        TFunction<void(Gs2::SeasonRating::Model::FVotePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FVoteDomain::Subscribe(
        TFunction<void(Gs2::SeasonRating::Model::FVotePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::SeasonRating::Model::Cache::FVoteCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SeasonRating::Model::Cache::FVoteCache::CreateCacheKey(

            SeasonName,
            SessionName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SeasonRating::Domain::FGs2SeasonRatingDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QuerySeasonName = SeasonName;
        const TOptional<FString> QuerySessionName = SessionName;
        return Gs2->Cache->Subscribe(
            Gs2::SeasonRating::Model::FVote::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SeasonRating::Model::FVote>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QuerySeasonName, QuerySessionName]()
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
                    QuerySeasonName,
                    QuerySessionName
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
        const auto SubscriptionParentKey = Gs2::SeasonRating::Model::Cache::FVoteCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SeasonRating::Model::Cache::FVoteCache::CreateCacheKey(

            SeasonName,
            SessionName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::SeasonRating::Model::FVote::TypeName,
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
