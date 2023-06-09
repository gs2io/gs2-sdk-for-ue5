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
#include "../Model/Status.h"

namespace Gs2::Idle::Result
{
    class GS2IDLE_API FIncreaseMaximumIdleMinutesByStampSheetResult final : public TSharedFromThis<FIncreaseMaximumIdleMinutesByStampSheetResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        
    public:
        
        FIncreaseMaximumIdleMinutesByStampSheetResult();
        FIncreaseMaximumIdleMinutesByStampSheetResult(
            const FIncreaseMaximumIdleMinutesByStampSheetResult& From
        );
        ~FIncreaseMaximumIdleMinutesByStampSheetResult() = default;

        TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetResult> WithItem(const TSharedPtr<Model::FStatus> Item);

        TSharedPtr<Model::FStatus> GetItem() const;

        static TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetResult, ESPMode::ThreadSafe> FIncreaseMaximumIdleMinutesByStampSheetResultPtr;
}