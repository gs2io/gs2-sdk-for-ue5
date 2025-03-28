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

#include "Enhance/Domain/Model/Gs2EnhanceEzUserGameSessionDomain.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    TOptional<int64> FEzUserGameSessionDomain::AcquireExperience() const
    {
        return Domain->AcquireExperience;
    }

    TOptional<float> FEzUserGameSessionDomain::BonusRate() const
    {
        return Domain->BonusRate;
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
        Gs2::Enhance::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomainPtr FEzUserGameSessionDomain::Progress(
    ) const
    {
        return MakeShared<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>(
            Domain->Progress(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Enhance::Domain::Model::FEzEnhanceGameSessionDomainPtr FEzUserGameSessionDomain::Enhance(
    ) const
    {
        return MakeShared<Gs2::UE5::Enhance::Domain::Model::FEzEnhanceGameSessionDomain>(
            Domain->Enhance(
            ),
            GameSession,
            ConnectionValue
        );
    }
}
