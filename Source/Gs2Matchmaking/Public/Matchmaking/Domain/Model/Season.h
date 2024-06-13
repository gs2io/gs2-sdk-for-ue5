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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Matchmaking/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByPlayerIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeMatchmakingSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoSeasonMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoSeasonMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeJoinedSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeJoinedSeasonGatheringsByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Matchmaking::Domain
{
    class FGs2MatchmakingDomain;
    typedef TSharedPtr<FGs2MatchmakingDomain> FGs2MatchmakingDomainPtr;
}

namespace Gs2::Matchmaking::Domain::Model
{
    class FNamespaceDomain;
    class FGatheringDomain;
    class FGatheringAccessTokenDomain;
    class FRatingModelMasterDomain;
    class FRatingModelDomain;
    class FCurrentModelMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FSeasonDomain;
    class FSeasonAccessTokenDomain;
    class FSeasonModelDomain;
    class FSeasonModelMasterDomain;
    class FSeasonGatheringDomain;
    class FSeasonGatheringAccessTokenDomain;
    class FJoinedSeasonGatheringDomain;
    class FJoinedSeasonGatheringAccessTokenDomain;
    class FRatingDomain;
    class FRatingAccessTokenDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;

    class GS2MATCHMAKING_API FSeasonDomain:
        public TSharedFromThis<FSeasonDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr Service;
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> MatchmakingContextToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> GetMatchmakingContextToken() const
        {
            return MatchmakingContextToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> SeasonName;
        TOptional<int64> Season;
    private:

        FString ParentKey;

    public:

        FSeasonDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> SeasonName,
            const TOptional<int64> Season
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSeasonDomain(
            const FSeasonDomain& From
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeSeasonGatheringsIteratorPtr SeasonGatherings(
            const TOptional<int64> Tier = TOptional<int64>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSeasonGatherings(
            TFunction<void()> Callback
        );

        void UnsubscribeSeasonGatherings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeMatchmakingSeasonGatheringsIteratorPtr MatchmakingSeasonGatherings(
            const TOptional<int64> Tier = TOptional<int64>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMatchmakingSeasonGatherings(
            TFunction<void()> Callback
        );

        void UnsubscribeMatchmakingSeasonGatherings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingByUserIdIteratorPtr DoSeasonMatchmaking(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain> SeasonGathering(
            const int64 Tier,
            const FString SeasonGatheringName
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsByUserIdIteratorPtr JoinedSeasonGatherings(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeJoinedSeasonGatherings(
            TFunction<void()> Callback
        );

        void UnsubscribeJoinedSeasonGatherings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain> JoinedSeasonGathering(
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> SeasonName,
            TOptional<int64> Season,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> SeasonName,
            TOptional<FString> Season
        );

    };

    typedef TSharedPtr<FSeasonDomain> FSeasonDomainPtr;
}
