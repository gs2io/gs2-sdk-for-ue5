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
#include "Formation/Domain/Model/Gs2FormationEzPropertyFormGameSessionDomain.h"
#include "Formation/Model/Gs2FormationSlot.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FormationPropertyForm.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationOwnPropertyForm
{
    GENERATED_BODY()

    Gs2::UE5::Formation::Domain::Model::FEzPropertyFormGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FormationPropertyFormValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString PropertyId = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2FormationSlot> Slots = TArray<FGs2FormationSlot>();
};

inline FGs2FormationPropertyFormValue EzPropertyFormToFGs2FormationPropertyFormValue(
    const Gs2::UE5::Formation::Model::FEzPropertyFormPtr Model
)
{
    FGs2FormationPropertyFormValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationPropertyFormFunctionLibrary::EzPropertyFormToFGs2FormationPropertyFormValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.PropertyId = Model->GetPropertyId() ? *Model->GetPropertyId() : "";
    Value.Slots = Model->GetSlots() ? [&]
    {
        TArray<FGs2FormationSlot> r;
        for (auto v : *Model->GetSlots())
        {
            r.Add(EzSlotToFGs2FormationSlot(v));
        }
        return r;
    }() : TArray<FGs2FormationSlot>();
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzPropertyFormPtr FGs2FormationPropertyFormValueToEzPropertyForm(
    const FGs2FormationPropertyFormValue Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzPropertyForm>()
        ->WithName(Model.Name)
        ->WithPropertyId(Model.PropertyId)
        ->WithSlots([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Formation::Model::FEzSlotPtr>>();
            for (auto v : Model.Slots) {
                r->Add(FGs2FormationSlotToEzSlot(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2FormationPropertyFormFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};