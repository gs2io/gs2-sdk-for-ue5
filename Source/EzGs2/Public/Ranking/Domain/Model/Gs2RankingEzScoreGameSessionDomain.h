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
#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"
#include "Ranking/Model/Gs2RankingEzScore.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"
#include "Gs2RankingEzScoreGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeScoresIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzScoreGameSessionDomain final :
        public TSharedFromThis<FEzScoreGameSessionDomain>
    {
        Gs2::Ranking::Domain::Model::FScoreAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> CategoryName() const;
        TOptional<FString> ScorerUserId() const;
        TOptional<FString> UniqueId() const;

        FEzScoreGameSessionDomain(
            Gs2::Ranking::Domain::Model::FScoreAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetScoreTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Model::FEzScore>,
            public TSharedFromThis<FGetScoreTask>
        {
            TSharedPtr<FEzScoreGameSessionDomain> Self;

        public:
            explicit FGetScoreTask(
                TSharedPtr<FEzScoreGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Model::FEzScore>> Result
            ) override;
        };
        friend FGetScoreTask;

        TSharedPtr<FAsyncTask<FGetScoreTask>> GetScore(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Model::FEzScore>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzScoreGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzScoreGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Ranking::Model::FEzScorePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Ranking::Model::FEzScorePtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzScoreGameSessionDomain> FEzScoreGameSessionDomainPtr;
}
