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
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Model/Gs2GatewayEzWebSocketSession.h"
#include "Gs2GatewayEzWebSocketSessionDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    class EZGS2_API FEzWebSocketSessionDomain final :
        public TSharedFromThis<FEzWebSocketSessionDomain>
    {
        Gs2::Gateway::Domain::Model::FWebSocketSessionDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Protocol() const;
        TSharedPtr<TArray<FString>> SendConnectionIds() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzWebSocketSessionDomain(
            Gs2::Gateway::Domain::Model::FWebSocketSessionDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Gateway::Model::FEzWebSocketSession>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzWebSocketSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzWebSocketSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Gateway::Model::FEzWebSocketSessionPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Gateway::Model::FEzWebSocketSessionPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzWebSocketSessionDomain> FEzWebSocketSessionDomainPtr;
}
