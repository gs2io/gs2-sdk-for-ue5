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
#include "Gateway/Domain/Model/User.h"
#include "Gateway/Model/Gs2GatewayEzWebSocketSession.h"
#include "Gs2GatewayEzWebSocketSessionDomain.h"
#include "Gs2GatewayEzUserDomain.h"
#include "Gs2GatewayEzUserDomain.h"
#include "Gs2GatewayEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Gateway::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Protocol() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Gateway::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Gateway::Domain::Model::FEzWebSocketSessionDomainPtr WebSocketSession(
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
