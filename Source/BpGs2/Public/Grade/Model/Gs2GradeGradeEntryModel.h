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

#include "Grade/Model/Gs2GradeEzGradeEntryModel.h"
#include "Gs2GradeGradeEntryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2GradeGradeEntryModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 RankCapValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString PropertyIdRegex = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString GradeUpPropertyIdRegex = "";
};

inline FGs2GradeGradeEntryModel EzGradeEntryModelToFGs2GradeGradeEntryModel(
    const Gs2::UE5::Grade::Model::FEzGradeEntryModelPtr Model
)
{
    FGs2GradeGradeEntryModel Value;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.RankCapValue = Model->GetRankCapValue() ? *Model->GetRankCapValue() : 0;
    return Value;
}

inline Gs2::UE5::Grade::Model::FEzGradeEntryModelPtr FGs2GradeGradeEntryModelToEzGradeEntryModel(
    const FGs2GradeGradeEntryModel Model
)
{
    return MakeShared<Gs2::UE5::Grade::Model::FEzGradeEntryModel>()
        ->WithMetadata(Model.Metadata)
        ->WithRankCapValue(Model.RankCapValue);
}