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
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"
#include "Ranking/Model/Gs2RankingEzGlobalRankingSetting.h"
#include "Ranking/Model/Gs2RankingEzScope.h"
#include "Ranking/Model/Gs2RankingEzScore.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"
#include "Gs2RankingEzSubscribeUserDomain.h"
#include "Gs2RankingEzRankingDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeNearRankingsIterator.h"
#include "Gs2RankingEzRankingCategoryDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzRankingCategoryDomain final :
        public TSharedFromThis<FEzRankingCategoryDomain>
    {
        Gs2::Ranking::Domain::Model::FRankingCategoryDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<bool> Processing() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> CategoryName() const;
        TOptional<FString> AdditionalScopeName() const;

        FEzRankingCategoryDomain(
            Gs2::Ranking::Domain::Model::FRankingCategoryDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserDomainPtr SubscribeUser(
            const FString TargetUserId
        ) const;

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeNearRankingsIteratorPtr NearRankings(
            const int64 Score
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNearRankings(TFunction<void()> Callback);

        void UnsubscribeNearRankings(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking::Domain::Model::FEzRankingDomainPtr Ranking(
            const TOptional<FString> ScorerUserId = TOptional<FString>(),
            const TOptional<int64> Index = TOptional<int64>()
        ) const;

    };
    typedef TSharedPtr<FEzRankingCategoryDomain> FEzRankingCategoryDomainPtr;
}
