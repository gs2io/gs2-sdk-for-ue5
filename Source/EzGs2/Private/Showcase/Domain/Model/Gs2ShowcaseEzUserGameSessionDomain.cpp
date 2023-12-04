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

#include "Showcase/Domain/Model/Gs2ShowcaseEzUserGameSessionDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
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
        Gs2::Showcase::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Showcase::Domain::Model::FEzRandomShowcaseGameSessionDomainPtr FEzUserGameSessionDomain::RandomShowcase(
        const FString ShowcaseName
    ) const
    {
        return MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzRandomShowcaseGameSessionDomain>(
            Domain->RandomShowcase(
                ShowcaseName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Showcase::Domain::Model::FEzShowcaseGameSessionDomainPtr FEzUserGameSessionDomain::Showcase(
        const FString ShowcaseName
    ) const
    {
        return MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzShowcaseGameSessionDomain>(
            Domain->Showcase(
                ShowcaseName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
