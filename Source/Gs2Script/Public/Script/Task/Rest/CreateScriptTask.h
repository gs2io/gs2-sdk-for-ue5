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
#include "Script/Request/CreateScriptRequest.h"
#include "Script/Result/CreateScriptResult.h"

namespace Gs2::Script::Task::Rest
{
    class GS2SCRIPT_API FCreateScriptTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateScriptResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FCreateScriptRequestPtr Request;
    public:
        explicit FCreateScriptTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FCreateScriptRequestPtr Request
        );
        FCreateScriptTask(
            const FCreateScriptTask& From
        );
        virtual ~FCreateScriptTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateScriptResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateScriptTask, ESPMode::ThreadSafe> FCreateScriptTaskPtr;
}