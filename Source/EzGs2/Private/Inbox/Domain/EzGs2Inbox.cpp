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

#include "Inbox/Domain/EzGs2Inbox.h"

namespace Gs2::UE5::Inbox::Domain
{

    FEzGs2Inbox::FEzGs2Inbox(
        Gs2::Inbox::Domain::FGs2InboxDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Inbox::Domain::Model::FEzNamespaceDomainPtr FEzGs2Inbox::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::Inbox::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ConnectionValue
        );
    }

    FReceiveNotificationEvent& FEzGs2Inbox::OnReceiveNotification()
    {
        return ReceiveNotificationEvent;
    }
}
