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
#include "Distributor/Domain/Model/TransactionResult.h"
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
#include "Gs2DistributorEzTransactionResultDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    class EZGS2_API FEzTransactionResultDomain final :
        public TSharedFromThis<FEzTransactionResultDomain>
    {
        Gs2::Distributor::Domain::Model::FTransactionResultDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> TransactionId() const;

        FEzTransactionResultDomain(
            Gs2::Distributor::Domain::Model::FTransactionResultDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Distributor::Model::FEzTransactionResult>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzTransactionResultDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzTransactionResultDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Distributor::Model::FEzTransactionResultPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Distributor::Model::FEzTransactionResultPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzTransactionResultDomain> FEzTransactionResultDomainPtr;
}
