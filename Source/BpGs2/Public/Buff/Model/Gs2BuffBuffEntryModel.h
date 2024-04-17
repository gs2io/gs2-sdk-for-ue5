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
#include "Buff/Domain/Model/Gs2BuffEzBuffEntryModelDomain.h"
#include "Buff/Model/Gs2BuffBuffTargetModel.h"
#include "Buff/Model/Gs2BuffBuffTargetAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2BuffBuffEntryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2BuffBuffEntryModel
{
    GENERATED_BODY()

    Gs2::UE5::Buff::Domain::Model::FEzBuffEntryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2BuffBuffEntryModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString TargetType = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2BuffBuffTargetModel TargetModel = FGs2BuffBuffTargetModel();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2BuffBuffTargetAction TargetAction = FGs2BuffBuffTargetAction();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Expression = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ApplyPeriodScheduleEventId = "";
};

inline FGs2BuffBuffEntryModelValue EzBuffEntryModelToFGs2BuffBuffEntryModelValue(
    const Gs2::UE5::Buff::Model::FEzBuffEntryModelPtr Model
)
{
    FGs2BuffBuffEntryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffBuffEntryModelFunctionLibrary::EzBuffEntryModelToFGs2BuffBuffEntryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.TargetType = Model->GetTargetType() ? *Model->GetTargetType() : "";
    Value.TargetModel = Model->GetTargetModel() ? EzBuffTargetModelToFGs2BuffBuffTargetModel(Model->GetTargetModel()) : FGs2BuffBuffTargetModel();
    Value.TargetAction = Model->GetTargetAction() ? EzBuffTargetActionToFGs2BuffBuffTargetAction(Model->GetTargetAction()) : FGs2BuffBuffTargetAction();
    Value.Expression = Model->GetExpression() ? *Model->GetExpression() : "";
    Value.ApplyPeriodScheduleEventId = Model->GetApplyPeriodScheduleEventId() ? *Model->GetApplyPeriodScheduleEventId() : "";
    return Value;
}

inline Gs2::UE5::Buff::Model::FEzBuffEntryModelPtr FGs2BuffBuffEntryModelValueToEzBuffEntryModel(
    const FGs2BuffBuffEntryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Buff::Model::FEzBuffEntryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTargetType(Model.TargetType)
        ->WithTargetModel(FGs2BuffBuffTargetModelToEzBuffTargetModel(Model.TargetModel))
        ->WithTargetAction(FGs2BuffBuffTargetActionToEzBuffTargetAction(Model.TargetAction))
        ->WithExpression(Model.Expression)
        ->WithApplyPeriodScheduleEventId(Model.ApplyPeriodScheduleEventId);
}

UCLASS()
class BPGS2_API UGs2BuffBuffEntryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};