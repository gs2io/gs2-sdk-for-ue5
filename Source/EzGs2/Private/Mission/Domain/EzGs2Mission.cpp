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

#include "Mission/Domain/EzGs2Mission.h"

namespace Gs2::UE5::Mission::Domain
{

    FEzGs2Mission::FEzGs2Mission(
        Gs2::Mission::Domain::FGs2MissionDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Mission::Domain::Model::FEzNamespaceDomainPtr FEzGs2Mission::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ConnectionValue
        );
    }

    FCompleteNotificationEvent& FEzGs2Mission::OnCompleteNotification()
    {
        return CompleteNotificationEvent;
    }
}
