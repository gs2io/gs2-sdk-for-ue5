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

#include "Formation/Model/Gs2FormationEzAcquireAction.h"
#include "Gs2FormationAcquireAction.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationAcquireAction
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Request = "";
};

inline FGs2FormationAcquireAction EzAcquireActionToFGs2FormationAcquireAction(
    const Gs2::UE5::Formation::Model::FEzAcquireActionPtr Model
)
{
    FGs2FormationAcquireAction Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.Request = Model->GetRequest() ? *Model->GetRequest() : "";
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzAcquireActionPtr FGs2FormationAcquireActionToEzAcquireAction(
    const FGs2FormationAcquireAction Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzAcquireAction>()
        ->WithAction(Model.Action)
        ->WithRequest(Model.Request);
}