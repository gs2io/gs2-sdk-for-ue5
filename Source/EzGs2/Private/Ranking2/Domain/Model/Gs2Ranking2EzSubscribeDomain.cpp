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

#include "Ranking2/Domain/Model/Gs2Ranking2EzSubscribeDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzSubscribeDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSubscribeDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    FEzSubscribeDomain::FEzSubscribeDomain(
        Gs2::Ranking2::Domain::Model::FSubscribeDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeUserDomainPtr FEzSubscribeDomain::SubscribeUser(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeUserDomain>(
            Domain->SubscribeUser(
                TargetUserId
            ),
            ConnectionValue
        );
    }
}
