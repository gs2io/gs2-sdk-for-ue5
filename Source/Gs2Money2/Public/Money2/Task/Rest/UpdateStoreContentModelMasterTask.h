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
#include "Money2/Request/UpdateStoreContentModelMasterRequest.h"
#include "Money2/Result/UpdateStoreContentModelMasterResult.h"

namespace Gs2::Money2::Task::Rest
{
    class GS2MONEY2_API FUpdateStoreContentModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateStoreContentModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FUpdateStoreContentModelMasterRequestPtr Request;
    public:
        explicit FUpdateStoreContentModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FUpdateStoreContentModelMasterRequestPtr Request
        );
        FUpdateStoreContentModelMasterTask(
            const FUpdateStoreContentModelMasterTask& From
        );
        virtual ~FUpdateStoreContentModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateStoreContentModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateStoreContentModelMasterTask, ESPMode::ThreadSafe> FUpdateStoreContentModelMasterTaskPtr;
}