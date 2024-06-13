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

#include "Matchmaking/Domain/Model/SeasonModel.h"
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

    FSeasonModelDomain::FSeasonModelDomain(
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
            "SeasonModel"
        ))
    {
    }

    FSeasonModelDomain::FSeasonModelDomain(
        const FSeasonModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        SeasonName(From.SeasonName),
        ParentKey(From.ParentKey)
    {

    }

    FSeasonModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FSeasonModelDomain>& Self,
        const Request::FGetSeasonModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName);
        const auto Future = Self->Client->GetSeasonModel(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "SeasonModel"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FSeasonModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FSeasonModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonModelDomain::FGetTask>> FSeasonModelDomain::Get(
        Request::FGetSeasonModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FSeasonModelDomain::CreateCacheParentKey(
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

    FString FSeasonModelDomain::CreateCacheKey(
        TOptional<FString> SeasonName
    )
    {
        return FString("") +
            (SeasonName.IsSet() ? *SeasonName : "null");
    }

    FSeasonModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FSeasonModelDomain> Self
    ): Self(Self)
    {

    }

    FSeasonModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FSeasonModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FSeasonModel>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonModelDomain::CreateCacheKey(
                Self->SeasonName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetSeasonModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Matchmaking::Domain::Model::FSeasonModelDomain::CreateCacheKey(
                    Self->SeasonName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FSeasonModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "seasonModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FSeasonModel>(
                Self->ParentKey,
                Gs2::Matchmaking::Domain::Model::FSeasonModelDomain::CreateCacheKey(
                    Self->SeasonName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonModelDomain::FModelTask>> FSeasonModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSeasonModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSeasonModelDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FSeasonModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FSeasonModel::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonModelDomain::CreateCacheKey(
                SeasonName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonModel>(obj));
            }
        );
    }

    void FSeasonModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FSeasonModel::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonModelDomain::CreateCacheKey(
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

