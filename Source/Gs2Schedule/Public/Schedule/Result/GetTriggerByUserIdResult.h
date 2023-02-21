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
#include "../Model/Trigger.h"

namespace Gs2::Schedule::Result
{
    class GS2SCHEDULE_API FGetTriggerByUserIdResult final : public TSharedFromThis<FGetTriggerByUserIdResult>
    {
        TSharedPtr<Model::FTrigger> ItemValue;
        
    public:
        
        FGetTriggerByUserIdResult();
        FGetTriggerByUserIdResult(
            const FGetTriggerByUserIdResult& From
        );
        ~FGetTriggerByUserIdResult() = default;

        TSharedPtr<FGetTriggerByUserIdResult> WithItem(const TSharedPtr<Model::FTrigger> Item);

        TSharedPtr<Model::FTrigger> GetItem() const;

        static TSharedPtr<FGetTriggerByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetTriggerByUserIdResult, ESPMode::ThreadSafe> FGetTriggerByUserIdResultPtr;
}