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

#include "Core/Gs2Core.h"
#include "Distributor/Request/UpdateDistributorModelMasterRequest.h"
#include "Distributor/Result/UpdateDistributorModelMasterResult.h"

namespace Gs2::Distributor::Task::Rest
{
    class GS2DISTRIBUTOR_API FUpdateDistributorModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateDistributorModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FUpdateDistributorModelMasterRequestPtr Request;
    public:
        explicit FUpdateDistributorModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FUpdateDistributorModelMasterRequestPtr Request
        );
        FUpdateDistributorModelMasterTask(
            const FUpdateDistributorModelMasterTask& From
        );
        virtual ~FUpdateDistributorModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateDistributorModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateDistributorModelMasterTask, ESPMode::ThreadSafe> FUpdateDistributorModelMasterTaskPtr;
}