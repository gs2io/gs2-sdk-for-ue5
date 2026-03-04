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
#include "Enhance/Domain/Model/Gs2EnhanceEzUnleashRateModelDomain.h"
#include "Enhance/Model/Gs2EnhanceUnleashRateEntryModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnhanceUnleashRateModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashRateModel
{
    GENERATED_BODY()

    Gs2::UE5::Enhance::Domain::Model::FEzUnleashRateModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashRateModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString TargetInventoryModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString GradeModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2EnhanceUnleashRateEntryModel> GradeEntries = TArray<FGs2EnhanceUnleashRateEntryModel>();
};

inline FGs2EnhanceUnleashRateModelValue EzUnleashRateModelToFGs2EnhanceUnleashRateModelValue(
    const Gs2::UE5::Enhance::Model::FEzUnleashRateModelPtr Model
)
{
    FGs2EnhanceUnleashRateModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceUnleashRateModelFunctionLibrary::EzUnleashRateModelToFGs2EnhanceUnleashRateModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.TargetInventoryModelId = Model->GetTargetInventoryModelId() ? *Model->GetTargetInventoryModelId() : "";
    Value.GradeModelId = Model->GetGradeModelId() ? *Model->GetGradeModelId() : "";
    Value.GradeEntries = Model->GetGradeEntries() ? [&]
    {
        TArray<FGs2EnhanceUnleashRateEntryModel> r;
        for (auto v : *Model->GetGradeEntries())
        {
            r.Add(EzUnleashRateEntryModelToFGs2EnhanceUnleashRateEntryModel(v));
        }
        return r;
    }() : TArray<FGs2EnhanceUnleashRateEntryModel>();
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzUnleashRateModelPtr FGs2EnhanceUnleashRateModelValueToEzUnleashRateModel(
    const FGs2EnhanceUnleashRateModelValue Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzUnleashRateModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTargetInventoryModelId(Model.TargetInventoryModelId)
        ->WithGradeModelId(Model.GradeModelId)
        ->WithGradeEntries([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModelPtr>>();
            for (auto v : Model.GradeEntries) {
                r->Add(FGs2EnhanceUnleashRateEntryModelToEzUnleashRateEntryModel(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2EnhanceUnleashRateModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};