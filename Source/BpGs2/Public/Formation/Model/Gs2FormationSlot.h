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

#include "Formation/Model/Gs2FormationEzSlot.h"
#include "Gs2FormationSlot.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationSlot
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    FString PropertyId = "";
    UPROPERTY(BlueprintReadWrite)
    FString Metadata = "";
};

inline FGs2FormationSlot EzSlotToFGs2FormationSlot(
    const Gs2::UE5::Formation::Model::FEzSlotPtr Model
)
{
    FGs2FormationSlot Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.PropertyId = Model->GetPropertyId() ? *Model->GetPropertyId() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzSlotPtr FGs2FormationSlotToEzSlot(
    const FGs2FormationSlot Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzSlot>()
        ->WithName(Model.Name)
        ->WithPropertyId(Model.PropertyId)
        ->WithMetadata(Model.Metadata);
}