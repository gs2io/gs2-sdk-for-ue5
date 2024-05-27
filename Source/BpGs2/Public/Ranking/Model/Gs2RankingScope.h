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

#include "Ranking/Model/Gs2RankingEzScope.h"
#include "Gs2RankingScope.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingScope
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 TargetDays = 0;
};

inline FGs2RankingScope EzScopeToFGs2RankingScope(
    const Gs2::UE5::Ranking::Model::FEzScopePtr Model
)
{
    FGs2RankingScope Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.TargetDays = Model->GetTargetDays() ? *Model->GetTargetDays() : 0;
    return Value;
}

inline Gs2::UE5::Ranking::Model::FEzScopePtr FGs2RankingScopeToEzScope(
    const FGs2RankingScope Model
)
{
    return MakeShared<Gs2::UE5::Ranking::Model::FEzScope>()
        ->WithName(Model.Name)
        ->WithTargetDays(Model.TargetDays);
}