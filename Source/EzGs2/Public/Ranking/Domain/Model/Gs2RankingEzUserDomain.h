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

#pragma once

#include "CoreMinimal.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"
#include "Ranking/Model/Gs2RankingEzScore.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"
#include "Gs2RankingEzSubscribeUserDomain.h"
#include "Gs2RankingEzRankingDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeNearRankingsIterator.h"
#include "Gs2RankingEzScoreDomain.h"
#include "Gs2RankingEzUserDomain.h"
#include "Gs2RankingEzUserDomain.h"
#include "Gs2RankingEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Ranking::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<bool> Processing() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Ranking::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserDomainPtr SubscribeUser(
            const FString CategoryName,
            const FString TargetUserId
        ) const;

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeNearRankingsIteratorPtr NearRankings(
            const FString CategoryName,
            const int64 Score
        ) const;

        Gs2::UE5::Ranking::Domain::Model::FEzRankingDomainPtr Ranking(
            const FString CategoryName
        ) const;

        Gs2::UE5::Ranking::Domain::Model::FEzScoreDomainPtr Score(
            const FString CategoryName,
            const FString ScorerUserId,
            const FString UniqueId
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
