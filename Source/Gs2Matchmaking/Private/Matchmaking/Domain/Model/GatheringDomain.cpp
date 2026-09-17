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

#include "Matchmaking/Domain/Model/Gathering.h"
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
#include "Matchmaking/Model/Cache/Gathering.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FGatheringDomain::FGatheringDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> GatheringName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        GatheringName(GatheringName),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Gathering"
        ))
    {
    }

    FGatheringDomain::FGatheringDomain(
        const FGatheringDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        GatheringName(From.GatheringName),
        ParentKey(From.ParentKey)
    {

    }

    FGatheringDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGatheringDomain>& Self,
        const Request::FUpdateGatheringByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGatheringDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGatheringName(Self->GatheringName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateGatheringByUserId(
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


        Gs2::Matchmaking::Model::Cache::FGatheringCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetGatheringName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringDomain::FUpdateTask>> FGatheringDomain::Update(
        Request::FUpdateGatheringByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FGatheringDomain::FPingTask::FPingTask(
        const TSharedPtr<FGatheringDomain>& Self,
        const Request::FPingByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGatheringDomain::FPingTask::FPingTask(
        const FPingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringDomain::FPingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGatheringName(Self->GatheringName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PingByUserId(
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


        Gs2::Matchmaking::Model::Cache::FGatheringCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetGatheringName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringDomain::FPingTask>> FGatheringDomain::Ping(
        Request::FPingByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPingTask>>(this->AsShared(), Request);
    }

    FGatheringDomain::FGetTask::FGetTask(
        const TSharedPtr<FGatheringDomain>& Self,
        const Request::FGetGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGatheringDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FGathering>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGatheringName(Self->GatheringName);
        const auto Future = Self->Client->GetGathering(
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


        Gs2::Matchmaking::Model::Cache::FGatheringCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Self->UserId,
            Request->GetGatheringName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringDomain::FGetTask>> FGatheringDomain::Get(
        Request::FGetGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGatheringDomain::FCancelMatchmakingTask::FCancelMatchmakingTask(
        const TSharedPtr<FGatheringDomain>& Self,
        const Request::FCancelMatchmakingByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGatheringDomain::FCancelMatchmakingTask::FCancelMatchmakingTask(
        const FCancelMatchmakingTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringDomain::FCancelMatchmakingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGatheringName(Self->GatheringName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CancelMatchmakingByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Matchmaking::Model::Cache::FGatheringCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetGatheringName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringDomain::FCancelMatchmakingTask>> FGatheringDomain::CancelMatchmaking(
        Request::FCancelMatchmakingByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCancelMatchmakingTask>>(this->AsShared(), Request);
    }

    FGatheringDomain::FEarlyCompleteTask::FEarlyCompleteTask(
        const TSharedPtr<FGatheringDomain>& Self,
        const Request::FEarlyCompleteByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGatheringDomain::FEarlyCompleteTask::FEarlyCompleteTask(
        const FEarlyCompleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringDomain::FEarlyCompleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGatheringName(Self->GatheringName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->EarlyCompleteByUserId(
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


        Gs2::Matchmaking::Model::Cache::FGatheringCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetGatheringName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGatheringDomain::FEarlyCompleteTask>> FGatheringDomain::EarlyComplete(
        Request::FEarlyCompleteByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEarlyCompleteTask>>(this->AsShared(), Request);
    }

    FString FGatheringDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> GatheringName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (GatheringName.IsSet() ? *GatheringName : "null") + ":" +
            ChildType;
    }

    FString FGatheringDomain::CreateCacheKey(
        TOptional<FString> GatheringName
    )
    {
        return FString("") +
            (GatheringName.IsSet() ? *GatheringName : "null");
    }

    FGatheringDomain::FModelTask::FModelTask(
        const TSharedPtr<FGatheringDomain> Self
    ): Self(Self)
    {

    }

    FGatheringDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FGathering>> Result
    )
    {
        const auto CacheParentKey = Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheKey(

            Self->GatheringName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Matchmaking::Model::FGathering::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Matchmaking::Model::FGatheringPtr Value;
                const auto CacheHit = Gs2::Matchmaking::Model::Cache::FGatheringCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->GatheringName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Matchmaking::Model::Cache::FGatheringCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->GatheringName,
                    TOptional<int32>(),
                    [Self](Gs2::Matchmaking::Model::FGatheringPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Matchmaking::Request::FGetGatheringRequest>()
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

    TSharedPtr<FAsyncTask<FGatheringDomain::FModelTask>> FGatheringDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGatheringDomain::FModelTask>>(this->AsShared());
    }

    void FGatheringDomain::Invalidate()
    {
        Gs2::Matchmaking::Model::Cache::FGatheringCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            GatheringName,
            TOptional<int32>()
        );
    }

    FGatheringDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FGatheringDomain>& Self,
        TFunction<void(Gs2::Matchmaking::Model::FGatheringPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FGatheringDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGatheringDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FGatheringDomain::FSubscribeWithInitialCallTask>> FGatheringDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Matchmaking::Model::FGatheringPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FGatheringDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FGatheringPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheKey(

            GatheringName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Matchmaking::Domain::FGs2MatchmakingDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryGatheringName = GatheringName;
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FGathering::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FGathering>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryGatheringName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FGatheringDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryGatheringName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FGatheringDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Matchmaking::Model::Cache::FGatheringCache::CreateCacheKey(

            GatheringName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FGathering::TypeName,
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
