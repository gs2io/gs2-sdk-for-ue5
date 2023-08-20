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
#include "Inventory/Request/DeleteBigItemByUserIdRequest.h"
#include "Inventory/Result/DeleteBigItemByUserIdResult.h"

namespace Gs2::Inventory::Task::Rest
{
    class GS2INVENTORY_API FDeleteBigItemByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDeleteBigItemByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDeleteBigItemByUserIdRequestPtr Request;
    public:
        explicit FDeleteBigItemByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDeleteBigItemByUserIdRequestPtr Request
        );
        FDeleteBigItemByUserIdTask(
            const FDeleteBigItemByUserIdTask& From
        );
        virtual ~FDeleteBigItemByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeleteBigItemByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeleteBigItemByUserIdTask, ESPMode::ThreadSafe> FDeleteBigItemByUserIdTaskPtr;
}