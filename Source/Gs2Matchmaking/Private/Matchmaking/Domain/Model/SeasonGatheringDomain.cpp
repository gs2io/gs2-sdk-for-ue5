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

#include "Matchmaking/Domain/Model/SeasonGathering.h"
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
#include "Matchmaking/Model/Cache/SeasonGathering.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FSeasonGatheringDomain::FSeasonGatheringDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> SeasonName,
        const TOptional<int64> Season,
        const TOptional<int64> Tier,
        const TOptional<FString> SeasonGatheringName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        SeasonName(SeasonName),
        Season(Season),
        Tier(Tier),
        SeasonGatheringName(SeasonGatheringName),
        ParentKey(Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            SeasonName,
            Season,
            "SeasonGathering"
        ))
    {
    }

    FSeasonGatheringDomain::FSeasonGatheringDomain(
        const FSeasonGatheringDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        SeasonName(From.SeasonName),
        Season(From.Season),
        Tier(From.Tier),
        SeasonGatheringName(From.SeasonGatheringName),
        ParentKey(From.ParentKey)
    {

    }

    FSeasonGatheringDomain::FGetTask::FGetTask(
        const TSharedPtr<FSeasonGatheringDomain>& Self,
        const Request::FGetSeasonGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonGatheringDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName)
            ->WithSeason(Self->Season)
            ->WithTier(Self->Tier)
            ->WithSeasonGatheringName(Self->SeasonGatheringName);
        const auto Future = Self->Client->GetSeasonGathering(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Self->UserId,
            ResultModel->GetItem()->GetSeasonName(),
            ResultModel->GetItem()->GetSeason().Get(int64{}),
            ResultModel->GetItem()->GetTier().Get(int64{}),
            Request->GetSeasonGatheringName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonGatheringDomain::FGetTask>> FSeasonGatheringDomain::Get(
        Request::FGetSeasonGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSeasonGatheringDomain::FVerifyIncludeParticipantTask::FVerifyIncludeParticipantTask(
        const TSharedPtr<FSeasonGatheringDomain>& Self,
        const Request::FVerifyIncludeParticipantByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonGatheringDomain::FVerifyIncludeParticipantTask::FVerifyIncludeParticipantTask(
        const FVerifyIncludeParticipantTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringDomain::FVerifyIncludeParticipantTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName)
            ->WithSeason(Self->Season)
            ->WithTier(Self->Tier)
            ->WithSeasonGatheringName(Self->SeasonGatheringName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->VerifyIncludeParticipantByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetSeasonName(),
            ResultModel->GetItem()->GetSeason().Get(int64{}),
            ResultModel->GetItem()->GetTier().Get(int64{}),
            Request->GetSeasonGatheringName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonGatheringDomain::FVerifyIncludeParticipantTask>> FSeasonGatheringDomain::VerifyIncludeParticipant(
        Request::FVerifyIncludeParticipantByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyIncludeParticipantTask>>(this->AsShared(), Request);
    }

    FSeasonGatheringDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSeasonGatheringDomain>& Self,
        const Request::FDeleteSeasonGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonGatheringDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName)
            ->WithSeason(Self->Season)
            ->WithTier(Self->Tier)
            ->WithSeasonGatheringName(Self->SeasonGatheringName);
        const auto Future = Self->Client->DeleteSeasonGathering(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

              if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Self->UserId,
            ResultModel->GetItem()->GetSeasonName(),
            ResultModel->GetItem()->GetSeason().Get(int64{}),
            ResultModel->GetItem()->GetTier().Get(int64{}),
            Request->GetSeasonGatheringName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonGatheringDomain::FDeleteTask>> FSeasonGatheringDomain::Delete(
        Request::FDeleteSeasonGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSeasonGatheringDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> SeasonName,
        TOptional<int64> Season,
        TOptional<int64> Tier,
        TOptional<FString> SeasonGatheringName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            (Season.IsSet() ? FString::FromInt(*Season) : "null") + ":" +
            (Tier.IsSet() ? FString::FromInt(*Tier) : "null") + ":" +
            (SeasonGatheringName.IsSet() ? *SeasonGatheringName : "null") + ":" +
            ChildType;
    }

    FString FSeasonGatheringDomain::CreateCacheKey(
        TOptional<int64> Tier,
        TOptional<FString> SeasonGatheringName
    )
    {
        return FString("") +
            (Tier.IsSet() ? FString::FromInt(*Tier) : "null") + ":" +
            (SeasonGatheringName.IsSet() ? *SeasonGatheringName : "null");
    }

    FSeasonGatheringDomain::FModelTask::FModelTask(
        const TSharedPtr<FSeasonGatheringDomain> Self
    ): Self(Self)
    {

    }

    FSeasonGatheringDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result
    )
    {
        const auto CacheParentKey = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            Self->SeasonName,
            Self->Season,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheKey(

            Self->Tier,
            Self->SeasonGatheringName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Matchmaking::Model::FSeasonGatheringPtr Value;
                const auto CacheHit = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->SeasonName,
                    Self->Season,
                    Self->Tier,
                    Self->SeasonGatheringName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->SeasonName,
                    Self->Season,
                    Self->Tier,
                    Self->SeasonGatheringName,
                    TOptional<int32>(),
                    [Self](Gs2::Matchmaking::Model::FSeasonGatheringPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Matchmaking::Request::FGetSeasonGatheringRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FSeasonGatheringDomain::FModelTask>> FSeasonGatheringDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSeasonGatheringDomain::FModelTask>>(this->AsShared());
    }

    void FSeasonGatheringDomain::Invalidate()
    {
        Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            SeasonName,
            Season,
            Tier,
            SeasonGatheringName,
            TOptional<int32>()
        );
    }

    FSeasonGatheringDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSeasonGatheringDomain>& Self,
        TFunction<void(Gs2::Matchmaking::Model::FSeasonGatheringPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FSeasonGatheringDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSeasonGatheringDomain::FSubscribeWithInitialCallTask>> FSeasonGatheringDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Matchmaking::Model::FSeasonGatheringPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FSeasonGatheringDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FSeasonGatheringPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            SeasonName,
            Season,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheKey(

            Tier,
            SeasonGatheringName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QuerySeasonName = SeasonName;
        const TOptional<int64> QuerySeason = Season;
        const TOptional<int64> QueryTier = Tier;
        const TOptional<FString> QuerySeasonGatheringName = SeasonGatheringName;
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QuerySeasonName, QuerySeason, QueryTier, QuerySeasonGatheringName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FSeasonGatheringDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QuerySeasonName,
                    QuerySeason,
                    QueryTier,
                    QuerySeasonGatheringName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSeasonGatheringDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            SeasonName,
            Season,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Matchmaking::Model::Cache::FSeasonGatheringCache::CreateCacheKey(

            Tier,
            SeasonGatheringName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
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
