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

#include "Formation/Model/Gs2FormationEzSlotModel.h"
#include "Gs2FormationSlotModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationSlotModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString PropertyRegex = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
};

inline FGs2FormationSlotModel EzSlotModelToFGs2FormationSlotModel(
    const Gs2::UE5::Formation::Model::FEzSlotModelPtr Model
)
{
    FGs2FormationSlotModel Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.PropertyRegex = Model->GetPropertyRegex() ? *Model->GetPropertyRegex() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzSlotModelPtr FGs2FormationSlotModelToEzSlotModel(
    const FGs2FormationSlotModel Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzSlotModel>()
        ->WithName(Model.Name)
        ->WithPropertyRegex(Model.PropertyRegex)
        ->WithMetadata(Model.Metadata);
}