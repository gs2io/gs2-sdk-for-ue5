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
#include "Identifier/Request/DeletePasswordRequest.h"
#include "Identifier/Result/DeletePasswordResult.h"

namespace Gs2::Identifier::Task::Rest
{
    class GS2IDENTIFIER_API FDeletePasswordTask final : public Gs2::Core::Util::TGs2Future<Result::FDeletePasswordResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDeletePasswordRequestPtr Request;
    public:
        explicit FDeletePasswordTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDeletePasswordRequestPtr Request
        );
        FDeletePasswordTask(
            const FDeletePasswordTask& From
        );
        virtual ~FDeletePasswordTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeletePasswordResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeletePasswordTask, ESPMode::ThreadSafe> FDeletePasswordTaskPtr;
}