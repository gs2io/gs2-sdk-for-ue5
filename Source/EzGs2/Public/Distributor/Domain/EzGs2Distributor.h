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
#include "Distributor/Domain/Gs2Distributor.h"
#include "Util/Net/Gs2Connection.h"
#include "Distributor/Domain/Model/Gs2DistributorEzNamespaceDomain.h"

namespace Gs2::UE5::Distributor::Domain
{
    DECLARE_EVENT_OneParam(Gs2Distributor, FAutoRunStampSheetNotificationEvent, Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr);
    typedef TSharedPtr<FAutoRunStampSheetNotificationEvent> FAutoRunStampSheetNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Distributor, FAutoRunTransactionNotificationEvent, Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr);
    typedef TSharedPtr<FAutoRunTransactionNotificationEvent> FAutoRunTransactionNotificationEventPtr;

    class EZGS2_API FEzGs2Distributor {
        Gs2::Distributor::Domain::FGs2DistributorDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FAutoRunStampSheetNotificationEvent AutoRunStampSheetNotificationEvent;
        FAutoRunTransactionNotificationEvent AutoRunTransactionNotificationEvent;

        FEzGs2Distributor(
            Gs2::Distributor::Domain::FGs2DistributorDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Distributor::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FAutoRunStampSheetNotificationEvent& OnAutoRunStampSheetNotification();

        FAutoRunTransactionNotificationEvent& OnAutoRunTransactionNotification();
    };
    typedef TSharedPtr<FEzGs2Distributor> FEzGs2DistributorPtr;
}
