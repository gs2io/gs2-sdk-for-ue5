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
#include "Limit/Domain/Model/Gs2LimitEzLimitModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2LimitLimitModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2LimitLimitModel
{
    GENERATED_BODY()

    Gs2::UE5::Limit::Domain::Model::FEzLimitModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2LimitLimitModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString LimitModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ResetType = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 ResetDayOfMonth = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ResetDayOfWeek = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 ResetHour = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 AnchorTimestamp = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 Days = 0;
};

inline FGs2LimitLimitModelValue EzLimitModelToFGs2LimitLimitModelValue(
    const Gs2::UE5::Limit::Model::FEzLimitModelPtr Model
)
{
    FGs2LimitLimitModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitLimitModelFunctionLibrary::EzLimitModelToFGs2LimitLimitModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.LimitModelId = Model->GetLimitModelId() ? *Model->GetLimitModelId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ResetType = Model->GetResetType() ? *Model->GetResetType() : "";
    Value.ResetDayOfMonth = Model->GetResetDayOfMonth() ? *Model->GetResetDayOfMonth() : 0;
    Value.ResetDayOfWeek = Model->GetResetDayOfWeek() ? *Model->GetResetDayOfWeek() : "";
    Value.ResetHour = Model->GetResetHour() ? *Model->GetResetHour() : 0;
    Value.AnchorTimestamp = Model->GetAnchorTimestamp() ? *Model->GetAnchorTimestamp() : 0;
    Value.Days = Model->GetDays() ? *Model->GetDays() : 0;
    return Value;
}

inline Gs2::UE5::Limit::Model::FEzLimitModelPtr FGs2LimitLimitModelValueToEzLimitModel(
    const FGs2LimitLimitModelValue Model
)
{
    return MakeShared<Gs2::UE5::Limit::Model::FEzLimitModel>()
        ->WithLimitModelId(Model.LimitModelId)
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithResetType(Model.ResetType)
        ->WithResetDayOfMonth(Model.ResetDayOfMonth)
        ->WithResetDayOfWeek(Model.ResetDayOfWeek)
        ->WithResetHour(Model.ResetHour)
        ->WithAnchorTimestamp(Model.AnchorTimestamp)
        ->WithDays(Model.Days);
}

UCLASS()
class BPGS2_API UGs2LimitLimitModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};