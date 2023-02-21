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

#include "Ranking/Domain/Model/Gs2RankingEzUserDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<bool> FEzUserDomain::Processing() const
    {
        return Domain->Processing;
    }

    TOptional<FString> FEzUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzUserDomain::FEzUserDomain(
        Gs2::Ranking::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserDomainPtr FEzUserDomain::SubscribeUser(
        const FString CategoryName,
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserDomain>(
            Domain->SubscribeUser(
                CategoryName,
                TargetUserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeNearRankingsIteratorPtr FEzUserDomain::NearRankings(
          const FString CategoryName,
          const int64 Score
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeNearRankingsIterator>(
            Domain->NearRankings(
                CategoryName,
                Score
            )
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzRankingDomainPtr FEzUserDomain::Ranking(
        const FString CategoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzRankingDomain>(
            Domain->Ranking(
                CategoryName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzScoreDomainPtr FEzUserDomain::Score(
        const FString CategoryName,
        const FString ScorerUserId,
        const FString UniqueId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzScoreDomain>(
            Domain->Score(
                CategoryName,
                ScorerUserId,
                UniqueId
            ),
            ProfileValue
        );
    }
}
