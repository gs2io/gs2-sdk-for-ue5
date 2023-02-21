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

namespace Gs2::Limit::Result
{
    class GS2LIMIT_API FCountUpByStampTaskResult final : public TSharedFromThis<FCountUpByStampTaskResult>
    {
        TSharedPtr<Model::FCounter> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FCountUpByStampTaskResult();
        FCountUpByStampTaskResult(
            const FCountUpByStampTaskResult& From
        );
        ~FCountUpByStampTaskResult() = default;

        TSharedPtr<FCountUpByStampTaskResult> WithItem(const TSharedPtr<Model::FCounter> Item);
        TSharedPtr<FCountUpByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FCounter> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FCountUpByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCountUpByStampTaskResult, ESPMode::ThreadSafe> FCountUpByStampTaskResultPtr;
}