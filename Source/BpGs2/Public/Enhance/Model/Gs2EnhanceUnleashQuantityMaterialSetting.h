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

#include "Enhance/Model/Gs2EnhanceEzUnleashQuantityMaterialSetting.h"
#include "Gs2EnhanceUnleashQuantityMaterialSetting.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashQuantityMaterialSetting
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString MatchType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString MaterialInventoryModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ItemModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Count = 0;
};

inline FGs2EnhanceUnleashQuantityMaterialSetting EzUnleashQuantityMaterialSettingToFGs2EnhanceUnleashQuantityMaterialSetting(
    const Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSettingPtr Model
)
{
    FGs2EnhanceUnleashQuantityMaterialSetting Value;
    Value.MatchType = Model->GetMatchType() ? *Model->GetMatchType() : "";
    Value.MaterialInventoryModelId = Model->GetMaterialInventoryModelId() ? *Model->GetMaterialInventoryModelId() : "";
    Value.ItemModelId = Model->GetItemModelId() ? *Model->GetItemModelId() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSettingPtr FGs2EnhanceUnleashQuantityMaterialSettingToEzUnleashQuantityMaterialSetting(
    const FGs2EnhanceUnleashQuantityMaterialSetting Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSetting>()
        ->WithMatchType(Model.MatchType)
        ->WithMaterialInventoryModelId(Model.MaterialInventoryModelId)
        ->WithItemModelId(Model.ItemModelId)
        ->WithCount(Model.Count);
}