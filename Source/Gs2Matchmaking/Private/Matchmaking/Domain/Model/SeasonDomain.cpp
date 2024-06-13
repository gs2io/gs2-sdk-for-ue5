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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Matchmaking::Domain::Model
{

    FSeasonDomain::FSeasonDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> SeasonName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        SeasonName(SeasonName),
        Season(Season),
        ParentKey(Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Season"
        ))
    {
    }

    FSeasonDomain::FSeasonDomain(
        const FSeasonDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        SeasonName(From.SeasonName),
        Season(From.Season),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonGatheringsIteratorPtr FSeasonDomain::SeasonGatherings(
        const TOptional<int64> Tier
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonGatheringsIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            Season,
            Tier
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeSeasonGatherings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                SeasonName,
                Season,
                "SeasonGathering"
            ),
            Callback
        );
    }

    void FSeasonDomain::UnsubscribeSeasonGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                SeasonName,
                Season,
                "SeasonGathering"
            ),
            CallbackID
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeMatchmakingSeasonGatheringsIteratorPtr FSeasonDomain::MatchmakingSeasonGatherings(
        const TOptional<int64> Tier
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeMatchmakingSeasonGatheringsIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            Season,
            Tier
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeMatchmakingSeasonGatherings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                SeasonName,
                Season,
                "SeasonGathering"
            ),
            Callback
        );
    }

    void FSeasonDomain::UnsubscribeMatchmakingSeasonGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                SeasonName,
                Season,
                "SeasonGathering"
            ),
            CallbackID
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingByUserIdIteratorPtr FSeasonDomain::DoSeasonMatchmaking(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            SeasonName,
            UserId,
            TimeOffsetToken
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain> FSeasonDomain::SeasonGathering(
        const int64 Tier,
        const FString SeasonGatheringName
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            SeasonName,
            Season,
            Tier,
            SeasonGatheringName == TEXT("") ? TOptional<FString>() : TOptional<FString>(SeasonGatheringName)
        );
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsByUserIdIteratorPtr FSeasonDomain::JoinedSeasonGatherings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            SeasonName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FSeasonDomain::SubscribeJoinedSeasonGatherings(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                TOptional<int64>(),
                "JoinedSeasonGathering"
            ),
            Callback
        );
    }

    void FSeasonDomain::UnsubscribeJoinedSeasonGatherings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
            Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                SeasonName,
                TOptional<int64>(),
                "JoinedSeasonGathering"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain> FSeasonDomain::JoinedSeasonGathering(
    )
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            SeasonName,
            Season
        );
    }

    FString FSeasonDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> SeasonName,
        TOptional<int64> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (SeasonName.IsSet() ? *SeasonName : "null") + ":" +
            (Season.IsSet() ? FString::Printf(TEXT("%lld"), *Season) : "null") + ":" +
            ChildType;
    }

    FString FSeasonDomain::CreateCacheKey(
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

