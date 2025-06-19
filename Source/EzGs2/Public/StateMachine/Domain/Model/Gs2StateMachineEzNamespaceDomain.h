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
#include "StateMachine/Domain/Model/Namespace.h"
#include "StateMachine/Model/Gs2StateMachineEzStatus.h"
#include "StateMachine/Model/Gs2StateMachineEzStackEntry.h"
#include "StateMachine/Model/Gs2StateMachineEzVariable.h"
#include "StateMachine/Model/Gs2StateMachineEzChangeStateEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzEmitEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzRandomStatus.h"
#include "StateMachine/Model/Gs2StateMachineEzRandomUsed.h"
#include "StateMachine/Model/Gs2StateMachineEzVerifyActionResult.h"
#include "StateMachine/Model/Gs2StateMachineEzConsumeActionResult.h"
#include "StateMachine/Model/Gs2StateMachineEzAcquireActionResult.h"
#include "StateMachine/Model/Gs2StateMachineEzTransactionResult.h"
#include "Gs2StateMachineEzUserDomain.h"
#include "Gs2StateMachineEzUserDomain.h"
#include "Gs2StateMachineEzUserGameSessionDomain.h"
#include "Gs2StateMachineEzNamespaceDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::StateMachine::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::StateMachine::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::StateMachine::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::StateMachine::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::StateMachine::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
