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
#include "Formation/Domain/Model/Gs2FormationEzFormGameSessionDomain.h"
#include "Formation/Model/Gs2FormationSlot.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FormationForm.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationOwnForm
{
    GENERATED_BODY()

    Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FormationFormValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 Index = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2FormationSlot> Slots = TArray<FGs2FormationSlot>();
};

inline FGs2FormationFormValue EzFormToFGs2FormationFormValue(
    const Gs2::UE5::Formation::Model::FEzFormPtr Model
)
{
    FGs2FormationFormValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationFormFunctionLibrary::EzFormToFGs2FormationFormValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Index = Model->GetIndex() ? *Model->GetIndex() : 0;
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

inline Gs2::UE5::Formation::Model::FEzFormPtr FGs2FormationFormValueToEzForm(
    const FGs2FormationFormValue Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzForm>()
        ->WithName(Model.Name)
        ->WithIndex(Model.Index)
        ->WithSlots([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Formation::Model::FEzSlotPtr>>();
            for (auto v : Model.Slots) {
                r->Add(FGs2FormationSlotToEzSlot(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2FormationFormFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};