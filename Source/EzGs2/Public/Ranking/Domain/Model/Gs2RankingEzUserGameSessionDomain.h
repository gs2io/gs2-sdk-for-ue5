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
#include "Ranking/Domain/Model/UserAccessToken.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"
#include "Ranking/Model/Gs2RankingEzScore.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"
#include "Gs2RankingEzRankingCategoryGameSessionDomain.h"
#include "Gs2RankingEzScoreGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeScoresIterator.h"
#include "Gs2RankingEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Ranking::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Ranking::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Ranking::Domain::Model::FEzRankingCategoryGameSessionDomainPtr RankingCategory(
            const FString CategoryName,
            const TOptional<FString> AdditionalScopeName = TOptional<FString>()
        ) const;

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeScoresIteratorPtr Scores(
            const FString CategoryName,
            const FString ScorerUserId
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeScores(TFunction<void()> Callback);

        void UnsubscribeScores(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomainPtr Score(
            const FString CategoryName,
            const FString ScorerUserId,
            const FString UniqueId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
