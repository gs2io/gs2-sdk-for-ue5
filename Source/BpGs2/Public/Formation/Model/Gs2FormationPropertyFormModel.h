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
#include "Formation/Domain/Model/Gs2FormationEzPropertyFormModelDomain.h"
#include "Formation/Model/Gs2FormationSlotModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FormationPropertyFormModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationPropertyFormModel
{
    GENERATED_BODY()

    Gs2::UE5::Formation::Domain::Model::FEzPropertyFormModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FormationPropertyFormModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2FormationSlotModel> Slots = TArray<FGs2FormationSlotModel>();
};

inline FGs2FormationPropertyFormModelValue EzPropertyFormModelToFGs2FormationPropertyFormModelValue(
    const Gs2::UE5::Formation::Model::FEzPropertyFormModelPtr Model
)
{
    FGs2FormationPropertyFormModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationPropertyFormModelFunctionLibrary::EzPropertyFormModelToFGs2FormationPropertyFormModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Slots = Model->GetSlots() ? [&]
    {
        TArray<FGs2FormationSlotModel> r;
        for (auto v : *Model->GetSlots())
        {
            r.Add(EzSlotModelToFGs2FormationSlotModel(v));
        }
        return r;
    }() : TArray<FGs2FormationSlotModel>();
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzPropertyFormModelPtr FGs2FormationPropertyFormModelValueToEzPropertyFormModel(
    const FGs2FormationPropertyFormModelValue Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzPropertyFormModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithSlots([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Formation::Model::FEzSlotModelPtr>>();
            for (auto v : Model.Slots) {
                r->Add(FGs2FormationSlotModelToEzSlotModel(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2FormationPropertyFormModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};