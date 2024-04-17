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
#include "../Model/BuffEntryModel.h"

namespace Gs2::Buff::Result
{
    class GS2BUFF_API FApplyBuffResult final : public TSharedFromThis<FApplyBuffResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FBuffEntryModel>>> ItemsValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FApplyBuffResult();
        FApplyBuffResult(
            const FApplyBuffResult& From
        );
        ~FApplyBuffResult() = default;

        TSharedPtr<FApplyBuffResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FBuffEntryModel>>> Items);
        TSharedPtr<FApplyBuffResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<TArray<TSharedPtr<Model::FBuffEntryModel>>> GetItems() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FApplyBuffResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FApplyBuffResult, ESPMode::ThreadSafe> FApplyBuffResultPtr;
}