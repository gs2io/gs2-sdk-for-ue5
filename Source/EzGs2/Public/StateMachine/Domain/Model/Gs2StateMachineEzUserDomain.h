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
#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Model/Gs2StateMachineEzStatus.h"
#include "StateMachine/Model/Gs2StateMachineEzStackEntry.h"
#include "StateMachine/Model/Gs2StateMachineEzVariable.h"
#include "StateMachine/Model/Gs2StateMachineEzChangeStateEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzEmitEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzEvent.h"
#include "StateMachine/Model/Gs2StateMachineEzRandomStatus.h"
#include "StateMachine/Model/Gs2StateMachineEzRandomUsed.h"
#include "Gs2StateMachineEzStatusDomain.h"
#include "Gs2StateMachineEzUserDomain.h"
#include "Gs2StateMachineEzUserDomain.h"
#include "Gs2StateMachineEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::StateMachine::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::StateMachine::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::StateMachine::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::StateMachine::Domain::Model::FEzStatusDomainPtr Status(
            const FString StatusName
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
