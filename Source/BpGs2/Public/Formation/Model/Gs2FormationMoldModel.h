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
#include "Formation/Domain/Model/Gs2FormationEzMoldModelDomain.h"
#include "Formation/Model/Gs2FormationFormModel.h"
#include "Gs2FormationMoldModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationMoldModel
{
    GENERATED_BODY()

    Gs2::UE5::Formation::Domain::Model::FEzMoldModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FormationMoldModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2FormationFormModelValue FormModel = FGs2FormationFormModelValue();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 InitialMaxCapacity = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 MaxCapacity = 0;
};

inline FGs2FormationMoldModelValue EzMoldModelToFGs2FormationMoldModelValue(
    const Gs2::UE5::Formation::Model::FEzMoldModelPtr Model
)
{
    FGs2FormationMoldModelValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.FormModel = Model->GetFormModel() ? EzFormModelToFGs2FormationFormModelValue(Model->GetFormModel()) : FGs2FormationFormModelValue();
    Value.InitialMaxCapacity = Model->GetInitialMaxCapacity() ? *Model->GetInitialMaxCapacity() : 0;
    Value.MaxCapacity = Model->GetMaxCapacity() ? *Model->GetMaxCapacity() : 0;
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzMoldModelPtr FGs2FormationMoldModelValueToEzMoldModel(
    const FGs2FormationMoldModelValue Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzMoldModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithFormModel(FGs2FormationFormModelValueToEzFormModel(Model.FormModel))
        ->WithInitialMaxCapacity(Model.InitialMaxCapacity)
        ->WithMaxCapacity(Model.MaxCapacity);
}

UCLASS()
class BPGS2_API UGs2FormationMoldModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};