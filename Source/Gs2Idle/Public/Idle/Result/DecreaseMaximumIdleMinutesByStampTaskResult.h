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
    class GS2IDLE_API FDecreaseMaximumIdleMinutesByStampTaskResult final : public TSharedFromThis<FDecreaseMaximumIdleMinutesByStampTaskResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FDecreaseMaximumIdleMinutesByStampTaskResult();
        FDecreaseMaximumIdleMinutesByStampTaskResult(
            const FDecreaseMaximumIdleMinutesByStampTaskResult& From
        );
        ~FDecreaseMaximumIdleMinutesByStampTaskResult() = default;

        TSharedPtr<FDecreaseMaximumIdleMinutesByStampTaskResult> WithItem(const TSharedPtr<Model::FStatus> Item);
        TSharedPtr<FDecreaseMaximumIdleMinutesByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FStatus> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FDecreaseMaximumIdleMinutesByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaximumIdleMinutesByStampTaskResult, ESPMode::ThreadSafe> FDecreaseMaximumIdleMinutesByStampTaskResultPtr;
}