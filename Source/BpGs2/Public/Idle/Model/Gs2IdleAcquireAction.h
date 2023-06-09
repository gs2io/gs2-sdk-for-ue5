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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"

#include "Idle/Model/Gs2IdleEzAcquireAction.h"
#include "Gs2IdleAcquireAction.generated.h"

USTRUCT(BlueprintType)
struct FGs2IdleAcquireAction
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(BlueprintReadWrite)
    FString Request = "";
};

inline TArray<FGs2IdleAcquireAction> EzAcquireActionToFGs2IdleAcquireAction(
    const TSharedPtr<TArray<Gs2::UE5::Idle::Model::FEzAcquireActionPtr>> Models
)
{
    TArray<FGs2IdleAcquireAction> Values;
    for (auto Model : *Models)
    {
        FGs2IdleAcquireAction Value;
        Value.Action = Model->GetAction() ? *Model->GetAction() : "";
        Value.Request = Model->GetRequest() ? *Model->GetRequest() : "";
        Values.Add(Value);
    }
    return Values;
}

inline Gs2::UE5::Idle::Model::FEzAcquireActionPtr FGs2IdleAcquireActionToEzAcquireAction(
    const FGs2IdleAcquireAction Model
)
{
    return MakeShared<Gs2::UE5::Idle::Model::FEzAcquireAction>()
        ->WithAction(Model.Action)
        ->WithRequest(Model.Request);
}