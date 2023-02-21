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
#include "Version/Request/DeleteVersionModelMasterRequest.h"
#include "Version/Result/DeleteVersionModelMasterResult.h"

namespace Gs2::Version::Task::Rest
{
    class GS2VERSION_API FDeleteVersionModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FDeleteVersionModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDeleteVersionModelMasterRequestPtr Request;
    public:
        explicit FDeleteVersionModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDeleteVersionModelMasterRequestPtr Request
        );
        FDeleteVersionModelMasterTask(
            const FDeleteVersionModelMasterTask& From
        );
        virtual ~FDeleteVersionModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeleteVersionModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeleteVersionModelMasterTask, ESPMode::ThreadSafe> FDeleteVersionModelMasterTaskPtr;
}