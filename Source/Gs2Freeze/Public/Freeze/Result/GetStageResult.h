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
#include "../Model/Stage.h"
#include "../Model/Microservice.h"

namespace Gs2::Freeze::Result
{
    class GS2FREEZE_API FGetStageResult final : public TSharedFromThis<FGetStageResult>
    {
        TSharedPtr<Model::FStage> ItemValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> SourceValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> CurrentValue;
        
    public:
        
        FGetStageResult();
        FGetStageResult(
            const FGetStageResult& From
        );
        ~FGetStageResult() = default;

        TSharedPtr<FGetStageResult> WithItem(const TSharedPtr<Model::FStage> Item);
        TSharedPtr<FGetStageResult> WithSource(const TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> Source);
        TSharedPtr<FGetStageResult> WithCurrent(const TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> Current);

        TSharedPtr<Model::FStage> GetItem() const;
        TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> GetSource() const;
        TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> GetCurrent() const;

        static TSharedPtr<FGetStageResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStageResult, ESPMode::ThreadSafe> FGetStageResultPtr;
}