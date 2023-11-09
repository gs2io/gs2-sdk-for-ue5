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
#include "Enhance/Domain/Model/Gs2EnhanceEzProgressGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnhanceProgress.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceOwnProgress
{
    GENERATED_BODY()

    Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2EnhanceProgressValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RateName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PropertyId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ExperienceValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    float Rate = 0;
};

inline FGs2EnhanceProgressValue EzProgressToFGs2EnhanceProgressValue(
    const Gs2::UE5::Enhance::Model::FEzProgressPtr Model
)
{
    FGs2EnhanceProgressValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceProgressFunctionLibrary::EzProgressToFGs2EnhanceProgressValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.RateName = Model->GetRateName() ? *Model->GetRateName() : "";
    Value.PropertyId = Model->GetPropertyId() ? *Model->GetPropertyId() : "";
    Value.ExperienceValue = Model->GetExperienceValue() ? *Model->GetExperienceValue() : 0;
    Value.Rate = Model->GetRate() ? *Model->GetRate() : 0;
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzProgressPtr FGs2EnhanceProgressValueToEzProgress(
    const FGs2EnhanceProgressValue Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzProgress>()
        ->WithName(Model.Name)
        ->WithRateName(Model.RateName)
        ->WithPropertyId(Model.PropertyId)
        ->WithExperienceValue(Model.ExperienceValue)
        ->WithRate(Model.Rate);
}

UCLASS()
class BPGS2_API UGs2EnhanceProgressFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};