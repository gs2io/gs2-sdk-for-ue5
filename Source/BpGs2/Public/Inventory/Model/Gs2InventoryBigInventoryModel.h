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
#include "Inventory/Domain/Model/Gs2InventoryEzBigInventoryModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InventoryBigInventoryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryBigInventoryModel
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzBigInventoryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventoryBigInventoryModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
};

inline FGs2InventoryBigInventoryModelValue EzBigInventoryModelToFGs2InventoryBigInventoryModelValue(
    const Gs2::UE5::Inventory::Model::FEzBigInventoryModelPtr Model
)
{
    FGs2InventoryBigInventoryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryBigInventoryModelFunctionLibrary::EzBigInventoryModelToFGs2InventoryBigInventoryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzBigInventoryModelPtr FGs2InventoryBigInventoryModelValueToEzBigInventoryModel(
    const FGs2InventoryBigInventoryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzBigInventoryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata);
}

UCLASS()
class BPGS2_API UGs2InventoryBigInventoryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::BigItemModel", Category="Game Server Services|GS2-Inventory|Namespace|BigInventoryModel|BigItemModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="BigItemModel") FGs2InventoryBigItemModel BigItemModel(
        FGs2InventoryBigInventoryModel BigInventoryModel,
        FString ItemName
    );
};