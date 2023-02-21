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
#include "../Model/MissionGroupModel.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FDescribeMissionGroupModelsResult final : public TSharedFromThis<FDescribeMissionGroupModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FMissionGroupModel>>> ItemsValue;
        
    public:
        
        FDescribeMissionGroupModelsResult();
        FDescribeMissionGroupModelsResult(
            const FDescribeMissionGroupModelsResult& From
        );
        ~FDescribeMissionGroupModelsResult() = default;

        TSharedPtr<FDescribeMissionGroupModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FMissionGroupModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FMissionGroupModel>>> GetItems() const;

        static TSharedPtr<FDescribeMissionGroupModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeMissionGroupModelsResult, ESPMode::ThreadSafe> FDescribeMissionGroupModelsResultPtr;
}