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
#include "../Model/Mold.h"
#include "../Model/MoldModel.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FSubCapacityByStampTaskResult final : public TSharedFromThis<FSubCapacityByStampTaskResult>
    {
        TSharedPtr<Model::FMold> ItemValue;
        TSharedPtr<Model::FMoldModel> MoldModelValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FSubCapacityByStampTaskResult();
        FSubCapacityByStampTaskResult(
            const FSubCapacityByStampTaskResult& From
        );
        ~FSubCapacityByStampTaskResult() = default;

        TSharedPtr<FSubCapacityByStampTaskResult> WithItem(const TSharedPtr<Model::FMold> Item);
        TSharedPtr<FSubCapacityByStampTaskResult> WithMoldModel(const TSharedPtr<Model::FMoldModel> MoldModel);
        TSharedPtr<FSubCapacityByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FMold> GetItem() const;
        TSharedPtr<Model::FMoldModel> GetMoldModel() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FSubCapacityByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubCapacityByStampTaskResult, ESPMode::ThreadSafe> FSubCapacityByStampTaskResultPtr;
}