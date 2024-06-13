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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Matchmaking/Gs2Matchmaking.h"
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

    class GS2MATCHMAKING_API FSeasonAccessTokenDomain:
        public TSharedFromThis<FSeasonAccessTokenDomain>
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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> SeasonName;
        TOptional<int64> Season;
    private:

        FString ParentKey;

    public:

        FSeasonAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> SeasonName,
            const TOptional<int64> Season
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSeasonAccessTokenDomain(
            const FSeasonAccessTokenDomain& From
        );

        Gs2::Matchmaking::Domain::Iterator::FDoSeasonMatchmakingIteratorPtr DoSeasonMatchmaking(
        ) const;

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringAccessTokenDomain> SeasonGathering(
            const int64 Tier,
            const FString SeasonGatheringName
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIteratorPtr JoinedSeasonGatherings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeJoinedSeasonGatherings(
            TFunction<void()> Callback
        );

        void UnsubscribeJoinedSeasonGatherings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringAccessTokenDomain> JoinedSeasonGathering(
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> SeasonName,
            TOptional<FString> Season,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> SeasonName,
            TOptional<FString> Season
        );

    };

    typedef TSharedPtr<FSeasonAccessTokenDomain> FSeasonAccessTokenDomainPtr;
}
