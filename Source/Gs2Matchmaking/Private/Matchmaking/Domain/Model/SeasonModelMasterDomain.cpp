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

#include "Matchmaking/Domain/Model/SeasonModelMaster.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FSeasonModelMasterDomain::FSeasonModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SeasonName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        SeasonName(SeasonName),
        ParentKey(Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "SeasonModelMaster"
        ))
    {
    }

    FSeasonModelMasterDomain::FSeasonModelMasterDomain(
        const FSeasonModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        SeasonName(From.SeasonName),
        ParentKey(From.ParentKey)
    {

    }

    FSeasonModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FSeasonModelMasterDomain>& Self,
        const Request::FGetSeasonModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName);
        const auto Future = Self->Client->GetSeasonModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonModelMasterDomain::FGetTask>> FSeasonModelMasterDomain::Get(
        Request::FGetSeasonModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSeasonModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSeasonModelMasterDomain>& Self,
        const Request::FUpdateSeasonModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName);
        const auto Future = Self->Client->UpdateSeasonModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonModelMasterDomain::FUpdateTask>> FSeasonModelMasterDomain::Update(
        Request::FUpdateSeasonModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSeasonModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSeasonModelMasterDomain>& Self,
        const Request::FDeleteSeasonModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName);
        const auto Future = Self->Client->DeleteSeasonModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonModelMasterDomain::FDeleteTask>> FSeasonModelMasterDomain::Delete(
        Request::FDeleteSeasonModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSeasonModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> SeasonName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            ChildType;
    }

    FString FSeasonModelMasterDomain::CreateCacheKey(
        TOptional<FString> SeasonName
    )
    {
        return FString("") +
            (SeasonName.IsSet() ? *SeasonName : "null");
    }

    FSeasonModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FSeasonModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FSeasonModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FSeasonModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FSeasonModelMaster>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain::CreateCacheKey(
                Self->SeasonName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetSeasonModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain::CreateCacheKey(
                    Self->SeasonName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FSeasonModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "seasonModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FSeasonModelMaster>(
                Self->ParentKey,
                Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain::CreateCacheKey(
                    Self->SeasonName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonModelMasterDomain::FModelTask>> FSeasonModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSeasonModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSeasonModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FSeasonModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FSeasonModelMaster::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain::CreateCacheKey(
                SeasonName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonModelMaster>(obj));
            }
        );
    }

    void FSeasonModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FSeasonModelMaster::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonModelMasterDomain::CreateCacheKey(
                SeasonName
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

