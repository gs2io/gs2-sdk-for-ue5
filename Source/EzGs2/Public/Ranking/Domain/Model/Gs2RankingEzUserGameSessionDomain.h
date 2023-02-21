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
#include "Gs2RankingEzSubscribeUserGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeSubscribesByCategoryNameIterator.h"
#include "Gs2RankingEzRankingGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeRankingsIterator.h"
#include "Gs2RankingEzScoreGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeScoresIterator.h"
#include "Gs2RankingEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Ranking::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<bool> Processing() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Ranking::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FSubscribeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>,
            public TSharedFromThis<FSubscribeTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString CategoryName;
            FString TargetUserId;

        public:
            explicit FSubscribeTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString CategoryName,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>> Result
            ) override;
        };
        friend FSubscribeTask;

        TSharedPtr<FAsyncTask<FSubscribeTask>> Subscribe(
            FString CategoryName,
            FString TargetUserId
        );

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeSubscribesByCategoryNameIteratorPtr SubscribeUsers(
            const FString CategoryName
        ) const;

        Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomainPtr SubscribeUser(
            const FString CategoryName,
            const FString TargetUserId
        ) const;

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeRankingsIteratorPtr Rankings(
            const FString CategoryName
        ) const;

        Gs2::UE5::Ranking::Domain::Model::FEzRankingGameSessionDomainPtr Ranking(
            const FString CategoryName
        ) const;

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeScoresIteratorPtr Scores(
            const FString CategoryName,
            const FString ScorerUserId
        ) const;

        Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomainPtr Score(
            const FString CategoryName,
            const FString ScorerUserId,
            const FString UniqueId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
