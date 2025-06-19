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
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Model/Gs2DistributorEzConfig.h"
#include "Distributor/Model/Gs2DistributorEzDistributorModel.h"
#include "Distributor/Model/Gs2DistributorEzDistributeResource.h"
#include "Distributor/Model/Gs2DistributorEzStampSheetResult.h"
#include "Distributor/Model/Gs2DistributorEzBatchRequestPayload.h"
#include "Distributor/Model/Gs2DistributorEzBatchResultPayload.h"
#include "Distributor/Model/Gs2DistributorEzAcquireAction.h"
#include "Distributor/Model/Gs2DistributorEzConsumeAction.h"
#include "Distributor/Model/Gs2DistributorEzVerifyAction.h"
#include "Distributor/Model/Gs2DistributorEzTransactionResult.h"
#include "Distributor/Model/Gs2DistributorEzAcquireActionResult.h"
#include "Distributor/Model/Gs2DistributorEzConsumeActionResult.h"
#include "Distributor/Model/Gs2DistributorEzVerifyActionResult.h"
#include "Gs2DistributorEzStampSheetResultDomain.h"
#include "Gs2DistributorEzTransactionResultDomain.h"
#include "Gs2DistributorEzUserDomain.h"
#include "Gs2DistributorEzUserDomain.h"
#include "Gs2DistributorEzUserGameSessionDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Distributor::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Distributor::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Distributor::Domain::Model::FEzStampSheetResultDomainPtr StampSheetResult(
            const FString TransactionId
        ) const;

        Gs2::UE5::Distributor::Domain::Model::FEzTransactionResultDomainPtr TransactionResult(
            const FString TransactionId
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
