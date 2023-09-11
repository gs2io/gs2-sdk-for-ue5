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
#include "SkillTree/Domain/Model/Gs2SkillTreeEzNodeModelDomain.h"
#include "SkillTree/Model/Gs2SkillTreeConsumeAction.h"
#include "SkillTree/Model/Gs2SkillTreeAcquireAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SkillTreeNodeModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2SkillTreeNodeModel
{
    GENERATED_BODY()

    Gs2::UE5::SkillTree::Domain::Model::FEzNodeModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SkillTreeNodeModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2SkillTreeConsumeAction> ReleaseConsumeActions = TArray<FGs2SkillTreeConsumeAction>();
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2SkillTreeAcquireAction> ReturnAcquireActions = TArray<FGs2SkillTreeAcquireAction>();
    UPROPERTY(BlueprintReadOnly)
    float RestrainReturnRate = 0;
};

inline FGs2SkillTreeNodeModelValue EzNodeModelToFGs2SkillTreeNodeModelValue(
    const Gs2::UE5::SkillTree::Model::FEzNodeModelPtr Model
)
{
    FGs2SkillTreeNodeModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeNodeModelFunctionLibrary::EzNodeModelToFGs2SkillTreeNodeModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ReleaseConsumeActions = Model->GetReleaseConsumeActions() ? [&]
    {
        TArray<FGs2SkillTreeConsumeAction> r;
        for (auto v : *Model->GetReleaseConsumeActions())
        {
            r.Add(EzConsumeActionToFGs2SkillTreeConsumeAction(v));
        }
        return r;
    }() : TArray<FGs2SkillTreeConsumeAction>();
    Value.ReturnAcquireActions = Model->GetReturnAcquireActions() ? [&]
    {
        TArray<FGs2SkillTreeAcquireAction> r;
        for (auto v : *Model->GetReturnAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2SkillTreeAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2SkillTreeAcquireAction>();
    Value.RestrainReturnRate = Model->GetRestrainReturnRate() ? *Model->GetRestrainReturnRate() : 0;
    return Value;
}

inline Gs2::UE5::SkillTree::Model::FEzNodeModelPtr FGs2SkillTreeNodeModelValueToEzNodeModel(
    const FGs2SkillTreeNodeModelValue Model
)
{
    return MakeShared<Gs2::UE5::SkillTree::Model::FEzNodeModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithReleaseConsumeActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SkillTree::Model::FEzConsumeActionPtr>>();
            for (auto v : Model.ReleaseConsumeActions) {
                r->Add(FGs2SkillTreeConsumeActionToEzConsumeAction(v));
            }
            return r;
        }())
        ->WithReturnAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SkillTree::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.ReturnAcquireActions) {
                r->Add(FGs2SkillTreeAcquireActionToEzAcquireAction(v));
            }
            return r;
        }())
        ->WithRestrainReturnRate(Model.RestrainReturnRate);
}

UCLASS()
class BPGS2_API UGs2SkillTreeNodeModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};