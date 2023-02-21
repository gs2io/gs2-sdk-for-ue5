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
#include "Inventory/Request/VerifyReferenceOfRequest.h"
#include "Inventory/Result/VerifyReferenceOfResult.h"

namespace Gs2::Inventory::Task::Rest
{
    class GS2INVENTORY_API FVerifyReferenceOfTask final : public Gs2::Core::Util::TGs2Future<Result::FVerifyReferenceOfResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FVerifyReferenceOfRequestPtr Request;
    public:
        explicit FVerifyReferenceOfTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FVerifyReferenceOfRequestPtr Request
        );
        FVerifyReferenceOfTask(
            const FVerifyReferenceOfTask& From
        );
        virtual ~FVerifyReferenceOfTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FVerifyReferenceOfResultPtr> Result) override;
    };
    typedef TSharedPtr<FVerifyReferenceOfTask, ESPMode::ThreadSafe> FVerifyReferenceOfTaskPtr;
}