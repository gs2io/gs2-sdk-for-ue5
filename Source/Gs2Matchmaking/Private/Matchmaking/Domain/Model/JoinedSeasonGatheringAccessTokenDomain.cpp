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

#include "Matchmaking/Domain/Model/JoinedSeasonGatheringAccessToken.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGathering.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FJoinedSeasonGatheringAccessTokenDomain::FJoinedSeasonGatheringAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> SeasonName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        SeasonName(SeasonName),
        Season(Season),
        ParentKey(Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            SeasonName,
            TOptional<int64>(),
            "JoinedSeasonGathering"
        ))
    {
    }

    FJoinedSeasonGatheringAccessTokenDomain::FJoinedSeasonGatheringAccessTokenDomain(
        const FJoinedSeasonGatheringAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        SeasonName(From.SeasonName),
        Season(From.Season),
        ParentKey(From.ParentKey)
    {

    }

    FJoinedSeasonGatheringAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FJoinedSeasonGatheringAccessTokenDomain>& Self,
        const Request::FGetJoinedSeasonGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJoinedSeasonGatheringAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJoinedSeasonGatheringAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FJoinedSeasonGathering>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSeasonName(Self->SeasonName)
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetJoinedSeasonGathering(
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
                const auto ParentKey = Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->SeasonName,
                    TOptional<int64>(),
                    "JoinedSeasonGathering"
                );
                const auto Key = Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
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

    TSharedPtr<FAsyncTask<FJoinedSeasonGatheringAccessTokenDomain::FGetTask>> FJoinedSeasonGatheringAccessTokenDomain::Get(
        Request::FGetJoinedSeasonGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FJoinedSeasonGatheringAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> SeasonName,
        TOptional<FString> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            (Season.IsSet() ? *Season : "null") + ":" +
            ChildType;
    }

    FString FJoinedSeasonGatheringAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FJoinedSeasonGatheringAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FJoinedSeasonGatheringAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FJoinedSeasonGatheringAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FJoinedSeasonGatheringAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FJoinedSeasonGathering>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FJoinedSeasonGathering> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FJoinedSeasonGathering>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetJoinedSeasonGatheringRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "joinedSeasonGathering")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FJoinedSeasonGathering>(
                Self->ParentKey,
                Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJoinedSeasonGatheringAccessTokenDomain::FModelTask>> FJoinedSeasonGatheringAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FJoinedSeasonGatheringAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FJoinedSeasonGatheringAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FJoinedSeasonGathering>(obj));
            }
        );
    }

    void FJoinedSeasonGatheringAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain::CreateCacheKey(
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

