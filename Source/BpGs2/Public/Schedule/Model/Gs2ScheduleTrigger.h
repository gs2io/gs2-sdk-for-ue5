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
#include "Schedule/Domain/Model/Gs2ScheduleEzTriggerGameSessionDomain.h"
#include "Gs2ScheduleTrigger.generated.h"

USTRUCT(BlueprintType)
struct FGs2ScheduleOwnTrigger
{
    GENERATED_BODY()

    Gs2::UE5::Schedule::Domain::Model::FEzTriggerGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ScheduleTriggerValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString TriggerId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    int64 CreatedAt = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 ExpiresAt = 0;
};

inline FGs2ScheduleTriggerValue EzTriggerToFGs2ScheduleTriggerValue(
    const Gs2::UE5::Schedule::Model::FEzTriggerPtr Model
)
{
    FGs2ScheduleTriggerValue Value;
    Value.TriggerId = Model->GetTriggerId() ? *Model->GetTriggerId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    Value.ExpiresAt = Model->GetExpiresAt() ? *Model->GetExpiresAt() : 0;
    return Value;
}

inline Gs2::UE5::Schedule::Model::FEzTriggerPtr FGs2ScheduleTriggerValueToEzTrigger(
    const FGs2ScheduleTriggerValue Model
)
{
    return MakeShared<Gs2::UE5::Schedule::Model::FEzTrigger>()
        ->WithTriggerId(Model.TriggerId)
        ->WithName(Model.Name)
        ->WithCreatedAt(Model.CreatedAt)
        ->WithExpiresAt(Model.ExpiresAt);
}

UCLASS()
class BPGS2_API UGs2ScheduleTriggerFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};