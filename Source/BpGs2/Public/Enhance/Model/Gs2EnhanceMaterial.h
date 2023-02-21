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

#include "Enhance/Model/Gs2EnhanceEzMaterial.h"
#include "Gs2EnhanceMaterial.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceMaterial
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString MaterialItemSetId = "";
    UPROPERTY(BlueprintReadWrite)
    int32 Count = 0;
};

inline FGs2EnhanceMaterial EzMaterialToFGs2EnhanceMaterial(
    const Gs2::UE5::Enhance::Model::FEzMaterialPtr Model
)
{
    FGs2EnhanceMaterial Value;
    Value.MaterialItemSetId = Model->GetMaterialItemSetId() ? *Model->GetMaterialItemSetId() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzMaterialPtr FGs2EnhanceMaterialToEzMaterial(
    const FGs2EnhanceMaterial Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzMaterial>()
        ->WithMaterialItemSetId(Model.MaterialItemSetId)
        ->WithCount(Model.Count);
}