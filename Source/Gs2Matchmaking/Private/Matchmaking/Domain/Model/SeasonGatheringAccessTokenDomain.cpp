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

#include "Matchmaking/Domain/Model/SeasonGatheringAccessToken.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FSeasonGatheringAccessTokenDomain::FSeasonGatheringAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
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
        AccessToken(AccessToken),
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

    FSeasonGatheringAccessTokenDomain::FSeasonGatheringAccessTokenDomain(
        const FSeasonGatheringAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        SeasonName(From.SeasonName),
        Season(From.Season),
        Tier(From.Tier),
        SeasonGatheringName(From.SeasonGatheringName),
        ParentKey(From.ParentKey)
    {

    }

    FSeasonGatheringAccessTokenDomain::FVerifyIncludeParticipantTask::FVerifyIncludeParticipantTask(
        const TSharedPtr<FSeasonGatheringAccessTokenDomain>& Self,
        const Request::FVerifyIncludeParticipantRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonGatheringAccessTokenDomain::FVerifyIncludeParticipantTask::FVerifyIncludeParticipantTask(
        const FVerifyIncludeParticipantTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringAccessTokenDomain::FVerifyIncludeParticipantTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithSeasonName(Self->SeasonName)
            ->WithSeason(Self->Season)
            ->WithTier(Self->Tier)
            ->WithSeasonGatheringName(Self->SeasonGatheringName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->VerifyIncludeParticipant(
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

    TSharedPtr<FAsyncTask<FSeasonGatheringAccessTokenDomain::FVerifyIncludeParticipantTask>> FSeasonGatheringAccessTokenDomain::VerifyIncludeParticipant(
        Request::FVerifyIncludeParticipantRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyIncludeParticipantTask>>(this->AsShared(), Request);
    }

    FSeasonGatheringAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FSeasonGatheringAccessTokenDomain>& Self,
        const Request::FGetSeasonGatheringRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSeasonGatheringAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonGatheringAccessTokenDomain::FGetTask>> FSeasonGatheringAccessTokenDomain::Get(
        Request::FGetSeasonGatheringRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FSeasonGatheringAccessTokenDomain::CreateCacheParentKey(
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

    FString FSeasonGatheringAccessTokenDomain::CreateCacheKey(
        TOptional<int64> Tier,
        TOptional<FString> SeasonGatheringName
    )
    {
        return FString("") +
            (Tier.IsSet() ? FString::FromInt(*Tier) : "null") + ":" + 
            (SeasonGatheringName.IsSet() ? *SeasonGatheringName : "null");
    }

    FSeasonGatheringAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSeasonGatheringAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSeasonGatheringAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSeasonGatheringAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FSeasonGathering>(
            Self->ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain::CreateCacheKey(
                Self->Tier,
                Self->SeasonGatheringName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Matchmaking::Request::FGetSeasonGatheringRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain::CreateCacheKey(
                    Self->Tier,
                    Self->SeasonGatheringName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "seasonGathering")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Matchmaking::Model::FSeasonGathering>(
                Self->ParentKey,
                Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain::CreateCacheKey(
                    Self->Tier,
                    Self->SeasonGatheringName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSeasonGatheringAccessTokenDomain::FModelTask>> FSeasonGatheringAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSeasonGatheringAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSeasonGatheringAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Matchmaking::Model::FSeasonGatheringPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain::CreateCacheKey(
                Tier,
                SeasonGatheringName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>(obj));
            }
        );
    }

    void FSeasonGatheringAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            ParentKey,
            Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain::CreateCacheKey(
                Tier,
                SeasonGatheringName
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

