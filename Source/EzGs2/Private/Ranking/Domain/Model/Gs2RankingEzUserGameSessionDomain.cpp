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

#include "Ranking/Domain/Model/Gs2RankingEzUserGameSessionDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Ranking::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking::Domain::Model::FEzRankingCategoryGameSessionDomainPtr FEzUserGameSessionDomain::RankingCategory(
        const FString CategoryName,
        const TOptional<FString> AdditionalScopeName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzRankingCategoryGameSessionDomain>(
            Domain->RankingCategory(
                CategoryName,
                AdditionalScopeName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeScoresIteratorPtr FEzUserGameSessionDomain::Scores(
          const FString CategoryName,
          const FString ScorerUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeScoresIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            CategoryName,
            ScorerUserId
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeScores(TFunction<void()> Callback)
    {
        return Domain->SubscribeScores(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeScores(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeScores(
            CallbackId
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomainPtr FEzUserGameSessionDomain::Score(
        const FString CategoryName,
        const FString ScorerUserId,
        const FString UniqueId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>(
            Domain->Score(
                CategoryName,
                ScorerUserId,
                UniqueId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
