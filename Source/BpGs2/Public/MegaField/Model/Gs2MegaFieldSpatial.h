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
#include "MegaField/Domain/Model/Gs2MegaFieldEzSpatialGameSessionDomain.h"
#include "MegaField/Domain/Model/Gs2MegaFieldEzSpatialDomain.h"
#include "MegaField/Model/Gs2MegaFieldPosition.h"
#include "MegaField/Model/Gs2MegaFieldVector.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MegaFieldSpatial.generated.h"

USTRUCT(BlueprintType)
struct FGs2MegaFieldOwnSpatial
{
    GENERATED_BODY()

    Gs2::UE5::MegaField::Domain::Model::FEzSpatialGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MegaFieldSpatial
{
    GENERATED_BODY()

    Gs2::UE5::MegaField::Domain::Model::FEzSpatialDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MegaFieldSpatialValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString AreaModelName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString LayerModelName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2MegaFieldPosition Position = FGs2MegaFieldPosition();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2MegaFieldVector Vector = FGs2MegaFieldVector();
};

inline FGs2MegaFieldSpatialValue EzSpatialToFGs2MegaFieldSpatialValue(
    const Gs2::UE5::MegaField::Model::FEzSpatialPtr Model
)
{
    FGs2MegaFieldSpatialValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldSpatialFunctionLibrary::EzSpatialToFGs2MegaFieldSpatialValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.AreaModelName = Model->GetAreaModelName() ? *Model->GetAreaModelName() : "";
    Value.LayerModelName = Model->GetLayerModelName() ? *Model->GetLayerModelName() : "";
    Value.Position = Model->GetPosition() ? EzPositionToFGs2MegaFieldPosition(Model->GetPosition()) : FGs2MegaFieldPosition();
    Value.Vector = Model->GetVector() ? EzVectorToFGs2MegaFieldVector(Model->GetVector()) : FGs2MegaFieldVector();
    return Value;
}

inline Gs2::UE5::MegaField::Model::FEzSpatialPtr FGs2MegaFieldSpatialValueToEzSpatial(
    const FGs2MegaFieldSpatialValue Model
)
{
    return MakeShared<Gs2::UE5::MegaField::Model::FEzSpatial>()
        ->WithUserId(Model.UserId)
        ->WithAreaModelName(Model.AreaModelName)
        ->WithLayerModelName(Model.LayerModelName)
        ->WithPosition(FGs2MegaFieldPositionToEzPosition(Model.Position))
        ->WithVector(FGs2MegaFieldVectorToEzVector(Model.Vector));
}

UCLASS()
class BPGS2_API UGs2MegaFieldSpatialFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};