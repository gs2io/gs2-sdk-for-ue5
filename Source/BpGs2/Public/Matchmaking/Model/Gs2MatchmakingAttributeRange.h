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

#include "Matchmaking/Model/Gs2MatchmakingEzAttributeRange.h"
#include "Gs2MatchmakingAttributeRange.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingAttributeRange
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Min = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Max = 0;
};

inline FGs2MatchmakingAttributeRange EzAttributeRangeToFGs2MatchmakingAttributeRange(
    const Gs2::UE5::Matchmaking::Model::FEzAttributeRangePtr Model
)
{
    FGs2MatchmakingAttributeRange Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Min = Model->GetMin() ? *Model->GetMin() : 0;
    Value.Max = Model->GetMax() ? *Model->GetMax() : 0;
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzAttributeRangePtr FGs2MatchmakingAttributeRangeToEzAttributeRange(
    const FGs2MatchmakingAttributeRange Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>()
        ->WithName(Model.Name)
        ->WithMin(Model.Min)
        ->WithMax(Model.Max);
}