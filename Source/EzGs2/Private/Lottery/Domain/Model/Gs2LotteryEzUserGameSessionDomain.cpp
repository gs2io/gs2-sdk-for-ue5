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

#include "Lottery/Domain/Model/Gs2LotteryEzUserGameSessionDomain.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzUserGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

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
        Gs2::Lottery::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeBoxesIteratorPtr FEzUserGameSessionDomain::Boxes(
    ) const
    {
        return MakeShared<Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeBoxesIterator>(
            Domain->Boxes(
            )
        );
    }

    Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomainPtr FEzUserGameSessionDomain::BoxItems(
        const FString PrizeTableName
    ) const
    {
        return MakeShared<Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomain>(
            Domain->BoxItems(
                PrizeTableName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeProbabilitiesIteratorPtr FEzUserGameSessionDomain::Probabilities(
          const FString LotteryName
    ) const
    {
        return MakeShared<Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeProbabilitiesIterator>(
            Domain->Probabilities(
                LotteryName
            )
        );
    }
}
