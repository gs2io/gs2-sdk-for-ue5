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
#include "Account/Request/AuthenticationRequest.h"
#include "Account/Result/AuthenticationResult.h"

namespace Gs2::Account::Task::Rest
{
    class GS2ACCOUNT_API FAuthenticationTask final : public Gs2::Core::Util::TGs2Future<Result::FAuthenticationResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FAuthenticationRequestPtr Request;
    public:
        explicit FAuthenticationTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FAuthenticationRequestPtr Request
        );
        FAuthenticationTask(
            const FAuthenticationTask& From
        );
        virtual ~FAuthenticationTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FAuthenticationResultPtr> Result) override;
    };
    typedef TSharedPtr<FAuthenticationTask, ESPMode::ThreadSafe> FAuthenticationTaskPtr;
}