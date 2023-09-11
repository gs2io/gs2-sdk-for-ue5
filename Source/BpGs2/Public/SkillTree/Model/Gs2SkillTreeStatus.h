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
#include "SkillTree/Domain/Model/Gs2SkillTreeEzStatusGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SkillTreeStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2SkillTreeOwnStatus
{
    GENERATED_BODY()

    Gs2::UE5::SkillTree::Domain::Model::FEzStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SkillTreeStatusValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString StatusId = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FString> ReleasedNodeNames = TArray<FString>();
};

inline FGs2SkillTreeStatusValue EzStatusToFGs2SkillTreeStatusValue(
    const Gs2::UE5::SkillTree::Model::FEzStatusPtr Model
)
{
    FGs2SkillTreeStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeStatusFunctionLibrary::EzStatusToFGs2SkillTreeStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.StatusId = Model->GetStatusId() ? *Model->GetStatusId() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.ReleasedNodeNames = Model->GetReleasedNodeNames() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetReleasedNodeNames())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::SkillTree::Model::FEzStatusPtr FGs2SkillTreeStatusValueToEzStatus(
    const FGs2SkillTreeStatusValue Model
)
{
    return MakeShared<Gs2::UE5::SkillTree::Model::FEzStatus>()
        ->WithStatusId(Model.StatusId)
        ->WithUserId(Model.UserId)
        ->WithReleasedNodeNames([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.ReleasedNodeNames) {
                r->Add(v);
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2SkillTreeStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};