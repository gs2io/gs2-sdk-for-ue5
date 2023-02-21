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

    UPROPERTY(BlueprintReadOnly)
    FString LimitModelId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    FString ResetType = "";
    UPROPERTY(BlueprintReadOnly)
    int32 ResetDayOfMonth = 0;
    UPROPERTY(BlueprintReadOnly)
    FString ResetDayOfWeek = "";
    UPROPERTY(BlueprintReadOnly)
    int32 ResetHour = 0;
};

inline FGs2LimitLimitModelValue EzLimitModelToFGs2LimitLimitModelValue(
    const Gs2::UE5::Limit::Model::FEzLimitModelPtr Model
)
{
    FGs2LimitLimitModelValue Value;
    Value.LimitModelId = Model->GetLimitModelId() ? *Model->GetLimitModelId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ResetType = Model->GetResetType() ? *Model->GetResetType() : "";
    Value.ResetDayOfMonth = Model->GetResetDayOfMonth() ? *Model->GetResetDayOfMonth() : 0;
    Value.ResetDayOfWeek = Model->GetResetDayOfWeek() ? *Model->GetResetDayOfWeek() : "";
    Value.ResetHour = Model->GetResetHour() ? *Model->GetResetHour() : 0;
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
        ->WithResetHour(Model.ResetHour);
}

UCLASS()
class BPGS2_API UGs2LimitLimitModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};