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
    class GS2SCHEDULE_API FDeleteTriggerByStampTaskResult final : public TSharedFromThis<FDeleteTriggerByStampTaskResult>
    {
        TSharedPtr<Model::FTrigger> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FDeleteTriggerByStampTaskResult();
        FDeleteTriggerByStampTaskResult(
            const FDeleteTriggerByStampTaskResult& From
        );
        ~FDeleteTriggerByStampTaskResult() = default;

        TSharedPtr<FDeleteTriggerByStampTaskResult> WithItem(const TSharedPtr<Model::FTrigger> Item);
        TSharedPtr<FDeleteTriggerByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FTrigger> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FDeleteTriggerByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteTriggerByStampTaskResult, ESPMode::ThreadSafe> FDeleteTriggerByStampTaskResultPtr;
}