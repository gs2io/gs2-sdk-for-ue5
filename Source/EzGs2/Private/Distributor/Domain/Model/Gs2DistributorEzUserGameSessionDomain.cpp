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

#include "Distributor/Domain/Model/Gs2DistributorEzUserGameSessionDomain.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Distributor::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Distributor::Domain::Model::FEzStampSheetResultGameSessionDomainPtr FEzUserGameSessionDomain::StampSheetResult(
        const FString TransactionId
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzStampSheetResultGameSessionDomain>(
            Domain->StampSheetResult(
                TransactionId
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Distributor::Domain::Model::FEzTransactionResultGameSessionDomainPtr FEzUserGameSessionDomain::TransactionResult(
        const FString TransactionId
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzTransactionResultGameSessionDomain>(
            Domain->TransactionResult(
                TransactionId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
