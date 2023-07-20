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

#include "Enchant/Domain/Model/Gs2EnchantEzUserGameSessionDomain.h"

namespace Gs2::UE5::Enchant::Domain::Model
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
        Gs2::Enchant::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterStatusesIteratorPtr FEzUserGameSessionDomain::BalanceParameterStatuses(
          const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterStatusesIterator>(
            Domain->BalanceParameterStatuses(
                ParameterName
            )
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterStatusGameSessionDomainPtr FEzUserGameSessionDomain::BalanceParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterStatusGameSessionDomain>(
            Domain->BalanceParameterStatus(
                ParameterName,
                PropertyId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterStatusesIteratorPtr FEzUserGameSessionDomain::RarityParameterStatuses(
          const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterStatusesIterator>(
            Domain->RarityParameterStatuses(
                ParameterName
            )
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomainPtr FEzUserGameSessionDomain::RarityParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomain>(
            Domain->RarityParameterStatus(
                ParameterName,
                PropertyId
            ),
            ProfileValue
        );
    }
}
