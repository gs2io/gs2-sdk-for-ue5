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
#include "Inventory/Request/DescribeBigItemModelMastersRequest.h"
#include "Inventory/Result/DescribeBigItemModelMastersResult.h"

namespace Gs2::Inventory::Task::Rest
{
    class GS2INVENTORY_API FDescribeBigItemModelMastersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeBigItemModelMastersResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeBigItemModelMastersRequestPtr Request;
    public:
        explicit FDescribeBigItemModelMastersTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeBigItemModelMastersRequestPtr Request
        );
        FDescribeBigItemModelMastersTask(
            const FDescribeBigItemModelMastersTask& From
        );
        virtual ~FDescribeBigItemModelMastersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeBigItemModelMastersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeBigItemModelMastersTask, ESPMode::ThreadSafe> FDescribeBigItemModelMastersTaskPtr;
}