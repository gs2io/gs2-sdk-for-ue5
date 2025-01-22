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

#include "Distributor/Domain/EzGs2Distributor.h"

namespace Gs2::UE5::Distributor::Domain
{

    FEzGs2Distributor::FEzGs2Distributor(
        Gs2::Distributor::Domain::FGs2DistributorDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Distributor::Domain::Model::FEzNamespaceDomainPtr FEzGs2Distributor::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ConnectionValue
        );
    }

    FAutoRunStampSheetNotificationEvent& FEzGs2Distributor::OnAutoRunStampSheetNotification()
    {
        return AutoRunStampSheetNotificationEvent;
    }

    FAutoRunTransactionNotificationEvent& FEzGs2Distributor::OnAutoRunTransactionNotification()
    {
        return AutoRunTransactionNotificationEvent;
    }
}
