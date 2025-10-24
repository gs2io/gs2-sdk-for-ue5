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

#include "Ranking/Domain/Model/Gs2RankingEzRankingCategoryDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzRankingCategoryDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<bool> FEzRankingCategoryDomain::Processing() const
    {
        return Domain->Processing;
    }

    TOptional<FString> FEzRankingCategoryDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRankingCategoryDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzRankingCategoryDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    TOptional<FString> FEzRankingCategoryDomain::AdditionalScopeName() const
    {
        return Domain->AdditionalScopeName;
    }

    FEzRankingCategoryDomain::FEzRankingCategoryDomain(
        Gs2::Ranking::Domain::Model::FRankingCategoryDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeNearRankingsIteratorPtr FEzRankingCategoryDomain::NearRankings(
        const int64 Score
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeNearRankingsIterator>(
            Domain,
            ConnectionValue,
            Score
        );
    }

    Gs2::Core::Domain::CallbackID FEzRankingCategoryDomain::SubscribeNearRankings(TFunction<void()> Callback)
    {
        return Domain->SubscribeNearRankings(
            Callback
        );
    }

    void FEzRankingCategoryDomain::UnsubscribeNearRankings(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeNearRankings(
            CallbackId
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserDomainPtr FEzRankingCategoryDomain::SubscribeUser(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserDomain>(
            Domain->SubscribeUser(
                TargetUserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzRankingDomainPtr FEzRankingCategoryDomain::Ranking(
        const TOptional<FString> ScorerUserId,
        const TOptional<int64> Index
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzRankingDomain>(
            Domain->Ranking(
                ScorerUserId,
                Index
            ),
            ConnectionValue
        );
    }
}
