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
#include "Matchmaking/Domain/Iterator/DescribeRatingsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsByUserIdIterator.h"

namespace Gs2::Matchmaking::Domain::Model
{
    class FNamespaceDomain;
    class FGatheringDomain;
    class FGatheringAccessTokenDomain;
    class FRatingModelMasterDomain;
    class FRatingModelDomain;
    class FCurrentRatingModelMasterDomain;
    class FRatingDomain;
    class FRatingAccessTokenDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2MATCHMAKING_API FBallotDomain:
        public TSharedFromThis<FBallotDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> RatingName;
        TOptional<FString> GatheringName;
        TOptional<int32> NumberOfPlayer;
        TOptional<FString> KeyId;
    private:

        FString ParentKey;

    public:

        FBallotDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> RatingName,
            const TOptional<FString> GatheringName,
            const TOptional<int32> NumberOfPlayer,
            const TOptional<FString> KeyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBallotDomain(
            const FBallotDomain& From
        );

        class GS2MATCHMAKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FBallotDomain>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBallotDomain> Self;
            const Request::FGetBallotByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBallotDomain> Self,
                const Request::FGetBallotByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotDomain>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetBallotByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> RatingName,
            TOptional<FString> GatheringName,
            TOptional<FString> NumberOfPlayer,
            TOptional<FString> KeyId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RatingName,
            TOptional<FString> GatheringName,
            TOptional<FString> NumberOfPlayer,
            TOptional<FString> KeyId
        );

        class GS2MATCHMAKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FBallot>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBallotDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBallotDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FBallot>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FBallotDomain> FBallotDomainPtr;
}
