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
#include "Identifier/Request/AttachSecurityPolicyRequest.h"
#include "Identifier/Result/AttachSecurityPolicyResult.h"

namespace Gs2::Identifier::Task::Rest
{
    class GS2IDENTIFIER_API FAttachSecurityPolicyTask final : public Gs2::Core::Util::TGs2Future<Result::FAttachSecurityPolicyResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FAttachSecurityPolicyRequestPtr Request;
    public:
        explicit FAttachSecurityPolicyTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FAttachSecurityPolicyRequestPtr Request
        );
        FAttachSecurityPolicyTask(
            const FAttachSecurityPolicyTask& From
        );
        virtual ~FAttachSecurityPolicyTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FAttachSecurityPolicyResultPtr> Result) override;
    };
    typedef TSharedPtr<FAttachSecurityPolicyTask, ESPMode::ThreadSafe> FAttachSecurityPolicyTaskPtr;
}