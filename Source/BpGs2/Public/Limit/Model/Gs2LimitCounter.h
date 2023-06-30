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
#include "Limit/Domain/Model/Gs2LimitEzCounterGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2LimitCounter.generated.h"

USTRUCT(BlueprintType)
struct FGs2LimitOwnCounter
{
    GENERATED_BODY()

    Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2LimitCounterValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString CounterId = "";
    UPROPERTY(BlueprintReadOnly)
    FString LimitName = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    int32 Count = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 CreatedAt = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 UpdatedAt = 0;
};

inline FGs2LimitCounterValue EzCounterToFGs2LimitCounterValue(
    const Gs2::UE5::Limit::Model::FEzCounterPtr Model
)
{
    FGs2LimitCounterValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitCounterFunctionLibrary::EzCounterToFGs2LimitCounterValue] Model parameter specification is missing."))
        return Value;
    }
    Value.CounterId = Model->GetCounterId() ? *Model->GetCounterId() : "";
    Value.LimitName = Model->GetLimitName() ? *Model->GetLimitName() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    Value.UpdatedAt = Model->GetUpdatedAt() ? *Model->GetUpdatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Limit::Model::FEzCounterPtr FGs2LimitCounterValueToEzCounter(
    const FGs2LimitCounterValue Model
)
{
    return MakeShared<Gs2::UE5::Limit::Model::FEzCounter>()
        ->WithCounterId(Model.CounterId)
        ->WithLimitName(Model.LimitName)
        ->WithName(Model.Name)
        ->WithCount(Model.Count)
        ->WithCreatedAt(Model.CreatedAt)
        ->WithUpdatedAt(Model.UpdatedAt);
}

UCLASS()
class BPGS2_API UGs2LimitCounterFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};