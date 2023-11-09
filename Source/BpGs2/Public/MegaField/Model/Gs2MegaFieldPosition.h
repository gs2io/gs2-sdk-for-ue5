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

#include "MegaField/Model/Gs2MegaFieldEzPosition.h"
#include "Gs2MegaFieldPosition.generated.h"

USTRUCT(BlueprintType)
struct FGs2MegaFieldPosition
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    float X = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    float Y = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    float Z = 0;
};

inline FGs2MegaFieldPosition EzPositionToFGs2MegaFieldPosition(
    const Gs2::UE5::MegaField::Model::FEzPositionPtr Model
)
{
    FGs2MegaFieldPosition Value;
    Value.X = Model->GetX() ? *Model->GetX() : 0;
    Value.Y = Model->GetY() ? *Model->GetY() : 0;
    Value.Z = Model->GetZ() ? *Model->GetZ() : 0;
    return Value;
}

inline Gs2::UE5::MegaField::Model::FEzPositionPtr FGs2MegaFieldPositionToEzPosition(
    const FGs2MegaFieldPosition Model
)
{
    return MakeShared<Gs2::UE5::MegaField::Model::FEzPosition>()
        ->WithX(Model.X)
        ->WithY(Model.Y)
        ->WithZ(Model.Z);
}