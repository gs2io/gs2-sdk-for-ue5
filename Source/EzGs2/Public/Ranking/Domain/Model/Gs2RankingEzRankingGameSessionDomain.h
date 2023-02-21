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

#pragma once

#include "CoreMinimal.h"
#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"
#include "Ranking/Model/Gs2RankingEzScore.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"
#include "Gs2RankingEzRankingGameSessionDomain.h"
#include "Gs2RankingEzScoreGameSessionDomain.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzRankingGameSessionDomain final :
        public TSharedFromThis<FEzRankingGameSessionDomain>
    {
        Gs2::Ranking::Domain::Model::FRankingAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> CategoryName() const;

        FEzRankingGameSessionDomain(
            Gs2::Ranking::Domain::Model::FRankingAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FPutScoreTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>,
            public TSharedFromThis<FPutScoreTask>
        {
            TSharedPtr<FEzRankingGameSessionDomain> Self;
            int64 Score;
            TOptional<FString> Metadata;

        public:
            explicit FPutScoreTask(
                TSharedPtr<FEzRankingGameSessionDomain> Self,
                int64 Score,
                TOptional<FString> Metadata = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>> Result
            ) override;
        };
        friend FPutScoreTask;

        TSharedPtr<FAsyncTask<FPutScoreTask>> PutScore(
            int64 Score,
            TOptional<FString> Metadata = TOptional<FString>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Model::FEzRanking>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzRankingGameSessionDomain> Self;
            FString ScorerUserId;

        public:
            explicit FModelTask(
                TSharedPtr<FEzRankingGameSessionDomain> Self,
                FString ScorerUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Ranking::Model::FEzRankingPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model(
            FString ScorerUserId
        );

    };
    typedef TSharedPtr<FEzRankingGameSessionDomain> FEzRankingGameSessionDomainPtr;
}
