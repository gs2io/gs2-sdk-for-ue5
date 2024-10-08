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
#include "../Model/Complete.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FBatchReceiveByStampTaskResult final : public TSharedFromThis<FBatchReceiveByStampTaskResult>
    {
        TSharedPtr<Model::FComplete> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FBatchReceiveByStampTaskResult();
        FBatchReceiveByStampTaskResult(
            const FBatchReceiveByStampTaskResult& From
        );
        ~FBatchReceiveByStampTaskResult() = default;

        TSharedPtr<FBatchReceiveByStampTaskResult> WithItem(const TSharedPtr<Model::FComplete> Item);
        TSharedPtr<FBatchReceiveByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FComplete> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FBatchReceiveByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchReceiveByStampTaskResult, ESPMode::ThreadSafe> FBatchReceiveByStampTaskResultPtr;
}