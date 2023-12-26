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
#include "Grade/Domain/Model/Gs2GradeEzGradeModelDomain.h"
#include "Grade/Model/Gs2GradeGradeEntryModel.h"
#include "Grade/Model/Gs2GradeAcquireActionRate.h"
#include "Core/BpGs2Constant.h"
#include "Gs2GradeGradeModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2GradeGradeModel
{
    GENERATED_BODY()

    Gs2::UE5::Grade::Domain::Model::FEzGradeModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2GradeGradeModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ExperienceModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2GradeGradeEntryModel> GradeEntries = TArray<FGs2GradeGradeEntryModel>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2GradeAcquireActionRate> AcquireActionRates = TArray<FGs2GradeAcquireActionRate>();
};

inline FGs2GradeGradeModelValue EzGradeModelToFGs2GradeGradeModelValue(
    const Gs2::UE5::Grade::Model::FEzGradeModelPtr Model
)
{
    FGs2GradeGradeModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeGradeModelFunctionLibrary::EzGradeModelToFGs2GradeGradeModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ExperienceModelId = Model->GetExperienceModelId() ? *Model->GetExperienceModelId() : "";
    Value.GradeEntries = Model->GetGradeEntries() ? [&]
    {
        TArray<FGs2GradeGradeEntryModel> r;
        for (auto v : *Model->GetGradeEntries())
        {
            r.Add(EzGradeEntryModelToFGs2GradeGradeEntryModel(v));
        }
        return r;
    }() : TArray<FGs2GradeGradeEntryModel>();
    Value.AcquireActionRates = Model->GetAcquireActionRates() ? [&]
    {
        TArray<FGs2GradeAcquireActionRate> r;
        for (auto v : *Model->GetAcquireActionRates())
        {
            r.Add(EzAcquireActionRateToFGs2GradeAcquireActionRate(v));
        }
        return r;
    }() : TArray<FGs2GradeAcquireActionRate>();
    return Value;
}

inline Gs2::UE5::Grade::Model::FEzGradeModelPtr FGs2GradeGradeModelValueToEzGradeModel(
    const FGs2GradeGradeModelValue Model
)
{
    return MakeShared<Gs2::UE5::Grade::Model::FEzGradeModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithExperienceModelId(Model.ExperienceModelId)
        ->WithGradeEntries([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Grade::Model::FEzGradeEntryModelPtr>>();
            for (auto v : Model.GradeEntries) {
                r->Add(FGs2GradeGradeEntryModelToEzGradeEntryModel(v));
            }
            return r;
        }())
        ->WithAcquireActionRates([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Grade::Model::FEzAcquireActionRatePtr>>();
            for (auto v : Model.AcquireActionRates) {
                r->Add(FGs2GradeAcquireActionRateToEzAcquireActionRate(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2GradeGradeModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};