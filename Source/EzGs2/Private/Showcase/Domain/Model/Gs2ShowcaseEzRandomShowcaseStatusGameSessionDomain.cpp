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

#include "Showcase/Domain/Model/Gs2ShowcaseEzRandomShowcaseStatusGameSessionDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzRandomShowcaseStatusGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRandomShowcaseStatusGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRandomShowcaseStatusGameSessionDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    FEzRandomShowcaseStatusGameSessionDomain::FEzRandomShowcaseStatusGameSessionDomain(
        Gs2::Showcase::Domain::Model::FRandomShowcaseStatusAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }
}
