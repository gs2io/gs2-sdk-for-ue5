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
#include "Gateway/Domain/Model/FirebaseTokenAccessToken.h"
#include "Gateway/Model/Gs2GatewayEzWebSocketSession.h"
#include "Gs2GatewayEzFirebaseTokenGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    class EZGS2_API FEzFirebaseTokenGameSessionDomain final :
        public TSharedFromThis<FEzFirebaseTokenGameSessionDomain>
    {
        Gs2::Gateway::Domain::Model::FFirebaseTokenAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzFirebaseTokenGameSessionDomain(
            Gs2::Gateway::Domain::Model::FFirebaseTokenAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

    };
    typedef TSharedPtr<FEzFirebaseTokenGameSessionDomain> FEzFirebaseTokenGameSessionDomainPtr;
}
