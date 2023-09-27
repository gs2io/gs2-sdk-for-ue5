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
#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Model/Gs2GatewayEzWebSocketSession.h"
#include "Gs2GatewayEzWebSocketSessionGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    class EZGS2_API FEzWebSocketSessionGameSessionDomain final :
        public TSharedFromThis<FEzWebSocketSessionGameSessionDomain>
    {
        Gs2::Gateway::Domain::Model::FWebSocketSessionAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Protocol() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzWebSocketSessionGameSessionDomain(
            Gs2::Gateway::Domain::Model::FWebSocketSessionAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FSetUserIdTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Gateway::Domain::Model::FEzWebSocketSessionGameSessionDomain>,
            public TSharedFromThis<FSetUserIdTask>
        {
            TSharedPtr<FEzWebSocketSessionGameSessionDomain> Self;
            TOptional<bool> AllowConcurrentAccess;

        public:
            explicit FSetUserIdTask(
                TSharedPtr<FEzWebSocketSessionGameSessionDomain> Self,
                TOptional<bool> AllowConcurrentAccess = TOptional<bool>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Gateway::Domain::Model::FEzWebSocketSessionGameSessionDomain>> Result
            ) override;
        };
        friend FSetUserIdTask;

        TSharedPtr<FAsyncTask<FSetUserIdTask>> SetUserId(
            TOptional<bool> AllowConcurrentAccess = TOptional<bool>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Gateway::Model::FEzWebSocketSession>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzWebSocketSessionGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzWebSocketSessionGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Gateway::Model::FEzWebSocketSessionPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Gateway::Model::FEzWebSocketSessionPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzWebSocketSessionGameSessionDomain> FEzWebSocketSessionGameSessionDomainPtr;
}
