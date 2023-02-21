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
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Model/Gs2DistributorEzDistributorModel.h"
#include "Distributor/Model/Gs2DistributorEzDistributeResource.h"
#include "Distributor/Model/Gs2DistributorEzStampSheetResult.h"
#include "Distributor/Model/Gs2DistributorEzAcquireAction.h"
#include "Distributor/Model/Gs2DistributorEzConsumeAction.h"
#include "Gs2DistributorEzStampSheetResultGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    class EZGS2_API FEzStampSheetResultGameSessionDomain final :
        public TSharedFromThis<FEzStampSheetResultGameSessionDomain>
    {
        Gs2::Distributor::Domain::Model::FStampSheetResultAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> TransactionId() const;

        FEzStampSheetResultGameSessionDomain(
            Gs2::Distributor::Domain::Model::FStampSheetResultAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetStampSheetResultTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Distributor::Model::FEzStampSheetResult>,
            public TSharedFromThis<FGetStampSheetResultTask>
        {
            TSharedPtr<FEzStampSheetResultGameSessionDomain> Self;

        public:
            explicit FGetStampSheetResultTask(
                TSharedPtr<FEzStampSheetResultGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Distributor::Model::FEzStampSheetResult>> Result
            ) override;
        };
        friend FGetStampSheetResultTask;

        TSharedPtr<FAsyncTask<FGetStampSheetResultTask>> GetStampSheetResult(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Distributor::Model::FEzStampSheetResult>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStampSheetResultGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStampSheetResultGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Distributor::Model::FEzStampSheetResultPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzStampSheetResultGameSessionDomain> FEzStampSheetResultGameSessionDomainPtr;
}
