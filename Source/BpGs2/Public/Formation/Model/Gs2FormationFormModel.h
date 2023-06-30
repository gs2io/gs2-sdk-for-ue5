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
#include "Formation/Domain/Model/Gs2FormationEzFormModelDomain.h"
#include "Formation/Model/Gs2FormationSlotModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FormationFormModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationFormModel
{
    GENERATED_BODY()

    Gs2::UE5::Formation::Domain::Model::FEzFormModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FormationFormModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2FormationSlotModel> Slots = TArray<FGs2FormationSlotModel>();
};

inline FGs2FormationFormModelValue EzFormModelToFGs2FormationFormModelValue(
    const Gs2::UE5::Formation::Model::FEzFormModelPtr Model
)
{
    FGs2FormationFormModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationFormModelFunctionLibrary::EzFormModelToFGs2FormationFormModelValue] Model parameter specification is missing."))
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

inline Gs2::UE5::Formation::Model::FEzFormModelPtr FGs2FormationFormModelValueToEzFormModel(
    const FGs2FormationFormModelValue Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzFormModel>()
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
class BPGS2_API UGs2FormationFormModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};