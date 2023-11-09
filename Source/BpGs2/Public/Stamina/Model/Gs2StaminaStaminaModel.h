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
#include "Stamina/Domain/Model/Gs2StaminaEzStaminaModelDomain.h"
#include "Stamina/Model/Gs2StaminaMaxStaminaTable.h"
#include "Stamina/Model/Gs2StaminaRecoverIntervalTable.h"
#include "Stamina/Model/Gs2StaminaRecoverValueTable.h"
#include "Core/BpGs2Constant.h"
#include "Gs2StaminaStaminaModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2StaminaStaminaModel
{
    GENERATED_BODY()

    Gs2::UE5::Stamina::Domain::Model::FEzStaminaModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2StaminaStaminaModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 RecoverIntervalMinutes = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 RecoverValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 InitialCapacity = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    bool IsOverflow = false;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 MaxCapacity = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2StaminaMaxStaminaTable MaxStaminaTable = FGs2StaminaMaxStaminaTable();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2StaminaRecoverIntervalTable RecoverIntervalTable = FGs2StaminaRecoverIntervalTable();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2StaminaRecoverValueTable RecoverValueTable = FGs2StaminaRecoverValueTable();
};

inline FGs2StaminaStaminaModelValue EzStaminaModelToFGs2StaminaStaminaModelValue(
    const Gs2::UE5::Stamina::Model::FEzStaminaModelPtr Model
)
{
    FGs2StaminaStaminaModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaStaminaModelFunctionLibrary::EzStaminaModelToFGs2StaminaStaminaModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.RecoverIntervalMinutes = Model->GetRecoverIntervalMinutes() ? *Model->GetRecoverIntervalMinutes() : 0;
    Value.RecoverValue = Model->GetRecoverValue() ? *Model->GetRecoverValue() : 0;
    Value.InitialCapacity = Model->GetInitialCapacity() ? *Model->GetInitialCapacity() : 0;
    Value.IsOverflow = Model->GetIsOverflow() ? *Model->GetIsOverflow() : false;
    Value.MaxCapacity = Model->GetMaxCapacity() ? *Model->GetMaxCapacity() : 0;
    Value.MaxStaminaTable = Model->GetMaxStaminaTable() ? EzMaxStaminaTableToFGs2StaminaMaxStaminaTable(Model->GetMaxStaminaTable()) : FGs2StaminaMaxStaminaTable();
    Value.RecoverIntervalTable = Model->GetRecoverIntervalTable() ? EzRecoverIntervalTableToFGs2StaminaRecoverIntervalTable(Model->GetRecoverIntervalTable()) : FGs2StaminaRecoverIntervalTable();
    Value.RecoverValueTable = Model->GetRecoverValueTable() ? EzRecoverValueTableToFGs2StaminaRecoverValueTable(Model->GetRecoverValueTable()) : FGs2StaminaRecoverValueTable();
    return Value;
}

inline Gs2::UE5::Stamina::Model::FEzStaminaModelPtr FGs2StaminaStaminaModelValueToEzStaminaModel(
    const FGs2StaminaStaminaModelValue Model
)
{
    return MakeShared<Gs2::UE5::Stamina::Model::FEzStaminaModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithRecoverIntervalMinutes(Model.RecoverIntervalMinutes)
        ->WithRecoverValue(Model.RecoverValue)
        ->WithInitialCapacity(Model.InitialCapacity)
        ->WithIsOverflow(Model.IsOverflow)
        ->WithMaxCapacity(Model.MaxCapacity)
        ->WithMaxStaminaTable(FGs2StaminaMaxStaminaTableToEzMaxStaminaTable(Model.MaxStaminaTable))
        ->WithRecoverIntervalTable(FGs2StaminaRecoverIntervalTableToEzRecoverIntervalTable(Model.RecoverIntervalTable))
        ->WithRecoverValueTable(FGs2StaminaRecoverValueTableToEzRecoverValueTable(Model.RecoverValueTable));
}

UCLASS()
class BPGS2_API UGs2StaminaStaminaModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};