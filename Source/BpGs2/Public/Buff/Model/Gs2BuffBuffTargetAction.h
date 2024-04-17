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

#include "Buff/Model/Gs2BuffEzBuffTargetAction.h"
#include "Buff/Model/Gs2BuffBuffTargetGrn.h"
#include "Gs2BuffBuffTargetAction.generated.h"

USTRUCT(BlueprintType)
struct FGs2BuffBuffTargetAction
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TargetActionName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TargetFieldName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2BuffBuffTargetGrn> ConditionGrns = TArray<FGs2BuffBuffTargetGrn>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    float Rate = 0;
};

inline FGs2BuffBuffTargetAction EzBuffTargetActionToFGs2BuffBuffTargetAction(
    const Gs2::UE5::Buff::Model::FEzBuffTargetActionPtr Model
)
{
    FGs2BuffBuffTargetAction Value;
    Value.TargetActionName = Model->GetTargetActionName() ? *Model->GetTargetActionName() : "";
    Value.TargetFieldName = Model->GetTargetFieldName() ? *Model->GetTargetFieldName() : "";
    Value.ConditionGrns = Model->GetConditionGrns() ? [&]
    {
        TArray<FGs2BuffBuffTargetGrn> r;
        for (auto v : *Model->GetConditionGrns())
        {r.Add(EzBuffTargetGrnToFGs2BuffBuffTargetGrn(v));
        }
        return r;
    }() : TArray<FGs2BuffBuffTargetGrn>();
    Value.Rate = Model->GetRate() ? *Model->GetRate() : 0;
    return Value;
}

inline Gs2::UE5::Buff::Model::FEzBuffTargetActionPtr FGs2BuffBuffTargetActionToEzBuffTargetAction(
    const FGs2BuffBuffTargetAction Model
)
{
    return MakeShared<Gs2::UE5::Buff::Model::FEzBuffTargetAction>()
        ->WithTargetActionName(Model.TargetActionName)
        ->WithTargetFieldName(Model.TargetFieldName)
        ->WithConditionGrns([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Buff::Model::FEzBuffTargetGrnPtr>>();
            for (auto v : Model.ConditionGrns) {
                r->Add(FGs2BuffBuffTargetGrnToEzBuffTargetGrn(v));
            }
            return r;
        }())
        ->WithRate(Model.Rate);
}