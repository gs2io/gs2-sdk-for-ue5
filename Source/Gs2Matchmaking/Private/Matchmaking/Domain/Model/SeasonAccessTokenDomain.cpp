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

#include "Matchmaking/Domain/Model/SeasonAccessToken.h"
#include "Matchmaking/Domain/Model/Season.h"
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

    FSeasonAccessTokenDomain::FSeasonAccessTokenDomain(
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
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Season"
        ))
    {
    }

    FSeasonAccessTokenDomain::FSeasonAccessTokenDomain(
        const FSeasonAccessTokenDomain& From
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

    Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingIteratorPtr FSeasonAccessTokenDomain::DoSeasonMatchmaking(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringAccessTokenDomain> FSeasonAccessTokenDomain::SeasonGathering(
        const int64 Tier,
        const FString SeasonGatheringName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonGatheringAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            SeasonName,
            Season,
            Tier,
            SeasonGatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonGatheringName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIteratorPtr FSeasonAccessTokenDomain::JoinedSeasonGatherings(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            SeasonName
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonAccessTokenDomain::SubscribeJoinedSeasonGatherings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                SeasonName,
                TOptional<int64>(),
                "JoinedSeasonGathering"
            ),
            Callback
        );
    }

    void FSeasonAccessTokenDomain::UnsubscribeJoinedSeasonGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                SeasonName,
                TOptional<int64>(),
                "JoinedSeasonGathering"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringAccessTokenDomain> FSeasonAccessTokenDomain::JoinedSeasonGathering(
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            SeasonName,
            Season
        );
    }

    FString FSeasonAccessTokenDomain::CreateCacheParentKey(
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

    FString FSeasonAccessTokenDomain::CreateCacheKey(
        TOptional<FString> SeasonName,
        TOptional<FString> Season
    )
    {
        return FString("") +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" + 
            (Season.IsSet() ? *Season : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

