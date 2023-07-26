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

#include "StateMachine/Domain/EzGs2StateMachine.h"

namespace Gs2::UE5::StateMachine::Domain
{

    FEzGs2StateMachine::FEzGs2StateMachine(
        Gs2::StateMachine::Domain::FGs2StateMachineDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::StateMachine::Domain::Model::FEzNamespaceDomainPtr FEzGs2StateMachine::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::StateMachine::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ProfileValue
        );
    }
}
