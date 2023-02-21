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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"

#include "MegaField/Model/Gs2MegaFieldEzMyPosition.h"
#include "MegaField/Model/Gs2MegaFieldPosition.h"
#include "MegaField/Model/Gs2MegaFieldVector.h"
#include "Gs2MegaFieldMyPosition.generated.h"

USTRUCT(BlueprintType)
struct FGs2MegaFieldMyPosition
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FGs2MegaFieldPosition Position = FGs2MegaFieldPosition();
    UPROPERTY(BlueprintReadWrite)
    FGs2MegaFieldVector Vector = FGs2MegaFieldVector();
    UPROPERTY(BlueprintReadOnly)
    float R = 0;
};

inline FGs2MegaFieldMyPosition EzMyPositionToFGs2MegaFieldMyPosition(
    const Gs2::UE5::MegaField::Model::FEzMyPositionPtr Model
)
{
    FGs2MegaFieldMyPosition Value;
    Value.Position = Model->GetPosition() ? EzPositionToFGs2MegaFieldPosition(Model->GetPosition()) : FGs2MegaFieldPosition();
    Value.Vector = Model->GetVector() ? EzVectorToFGs2MegaFieldVector(Model->GetVector()) : FGs2MegaFieldVector();
    Value.R = Model->GetR() ? *Model->GetR() : 0;
    return Value;
}

inline Gs2::UE5::MegaField::Model::FEzMyPositionPtr FGs2MegaFieldMyPositionToEzMyPosition(
    const FGs2MegaFieldMyPosition Model
)
{
    return MakeShared<Gs2::UE5::MegaField::Model::FEzMyPosition>()
        ->WithPosition(FGs2MegaFieldPositionToEzPosition(Model.Position))
        ->WithVector(FGs2MegaFieldVectorToEzVector(Model.Vector))
        ->WithR(Model.R);
}