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

#include "Buff/Model/Gs2BuffEzBuffTargetGrn.h"
#include "Gs2BuffBuffTargetGrn.generated.h"

USTRUCT(BlueprintType)
struct FGs2BuffBuffTargetGrn
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TargetModelName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TargetGrn = "";
};

inline FGs2BuffBuffTargetGrn EzBuffTargetGrnToFGs2BuffBuffTargetGrn(
    const Gs2::UE5::Buff::Model::FEzBuffTargetGrnPtr Model
)
{
    FGs2BuffBuffTargetGrn Value;
    Value.TargetModelName = Model->GetTargetModelName() ? *Model->GetTargetModelName() : "";
    Value.TargetGrn = Model->GetTargetGrn() ? *Model->GetTargetGrn() : "";
    return Value;
}

inline Gs2::UE5::Buff::Model::FEzBuffTargetGrnPtr FGs2BuffBuffTargetGrnToEzBuffTargetGrn(
    const FGs2BuffBuffTargetGrn Model
)
{
    return MakeShared<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>()
        ->WithTargetModelName(Model.TargetModelName)
        ->WithTargetGrn(Model.TargetGrn);
}