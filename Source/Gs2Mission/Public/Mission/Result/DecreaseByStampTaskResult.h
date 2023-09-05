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
#include "../Model/Counter.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FDecreaseByStampTaskResult final : public TSharedFromThis<FDecreaseByStampTaskResult>
    {
        TSharedPtr<Model::FCounter> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FDecreaseByStampTaskResult();
        FDecreaseByStampTaskResult(
            const FDecreaseByStampTaskResult& From
        );
        ~FDecreaseByStampTaskResult() = default;

        TSharedPtr<FDecreaseByStampTaskResult> WithItem(const TSharedPtr<Model::FCounter> Item);
        TSharedPtr<FDecreaseByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FCounter> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FDecreaseByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseByStampTaskResult, ESPMode::ThreadSafe> FDecreaseByStampTaskResultPtr;
}