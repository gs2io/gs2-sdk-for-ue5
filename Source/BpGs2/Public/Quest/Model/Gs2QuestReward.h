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

#include "Quest/Model/Gs2QuestEzReward.h"
#include "Gs2QuestReward.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestReward
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(BlueprintReadWrite)
    FString Request = "";
    UPROPERTY(BlueprintReadWrite)
    FString ItemId = "";
    UPROPERTY(BlueprintReadWrite)
    int32 Value = 0;
};

inline FGs2QuestReward EzRewardToFGs2QuestReward(
    const Gs2::UE5::Quest::Model::FEzRewardPtr Model
)
{
    FGs2QuestReward Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.Request = Model->GetRequest() ? *Model->GetRequest() : "";
    Value.ItemId = Model->GetItemId() ? *Model->GetItemId() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : 0;
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzRewardPtr FGs2QuestRewardToEzReward(
    const FGs2QuestReward Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzReward>()
        ->WithAction(Model.Action)
        ->WithRequest(Model.Request)
        ->WithItemId(Model.ItemId)
        ->WithValue(Model.Value);
}