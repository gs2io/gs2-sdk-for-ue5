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
    class GS2BUFF_API FApplyBuffByUserIdResult final : public TSharedFromThis<FApplyBuffByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FBuffEntryModel>>> ItemsValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FApplyBuffByUserIdResult();
        FApplyBuffByUserIdResult(
            const FApplyBuffByUserIdResult& From
        );
        ~FApplyBuffByUserIdResult() = default;

        TSharedPtr<FApplyBuffByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FBuffEntryModel>>> Items);
        TSharedPtr<FApplyBuffByUserIdResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<TArray<TSharedPtr<Model::FBuffEntryModel>>> GetItems() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FApplyBuffByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FApplyBuffByUserIdResult, ESPMode::ThreadSafe> FApplyBuffByUserIdResultPtr;
}