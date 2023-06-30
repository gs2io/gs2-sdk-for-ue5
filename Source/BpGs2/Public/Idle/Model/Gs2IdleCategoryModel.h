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
#include "Idle/Domain/Model/Gs2IdleEzCategoryModelDomain.h"
#include "Idle/Model/Gs2IdleAcquireActionList.h"
#include "Core/BpGs2Constant.h"
#include "Gs2IdleCategoryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2IdleCategoryModel
{
    GENERATED_BODY()

    Gs2::UE5::Idle::Domain::Model::FEzCategoryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2IdleCategoryModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    int32 RewardIntervalMinutes = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 DefaultMaximumIdleMinutes = 0;
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2IdleAcquireActionList> AcquireActions = TArray<FGs2IdleAcquireActionList>();
    UPROPERTY(BlueprintReadOnly)
    FString IdlePeriodScheduleId = "";
    UPROPERTY(BlueprintReadOnly)
    FString ReceivePeriodScheduleId = "";
};

inline FGs2IdleCategoryModelValue EzCategoryModelToFGs2IdleCategoryModelValue(
    const Gs2::UE5::Idle::Model::FEzCategoryModelPtr Model
)
{
    FGs2IdleCategoryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleCategoryModelFunctionLibrary::EzCategoryModelToFGs2IdleCategoryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.RewardIntervalMinutes = Model->GetRewardIntervalMinutes() ? *Model->GetRewardIntervalMinutes() : 0;
    Value.DefaultMaximumIdleMinutes = Model->GetDefaultMaximumIdleMinutes() ? *Model->GetDefaultMaximumIdleMinutes() : 0;
    Value.AcquireActions = Model->GetAcquireActions() ? [&]
    {
        TArray<FGs2IdleAcquireActionList> r;
        for (auto v : *Model->GetAcquireActions())
        {
            r.Add(EzAcquireActionListToFGs2IdleAcquireActionList(v));
        }
        return r;
    }() : TArray<FGs2IdleAcquireActionList>();
    Value.IdlePeriodScheduleId = Model->GetIdlePeriodScheduleId() ? *Model->GetIdlePeriodScheduleId() : "";
    Value.ReceivePeriodScheduleId = Model->GetReceivePeriodScheduleId() ? *Model->GetReceivePeriodScheduleId() : "";
    return Value;
}

inline Gs2::UE5::Idle::Model::FEzCategoryModelPtr FGs2IdleCategoryModelValueToEzCategoryModel(
    const FGs2IdleCategoryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Idle::Model::FEzCategoryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithRewardIntervalMinutes(Model.RewardIntervalMinutes)
        ->WithDefaultMaximumIdleMinutes(Model.DefaultMaximumIdleMinutes)
        ->WithAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Idle::Model::FEzAcquireActionListPtr>>();
            for (auto v : Model.AcquireActions) {
                r->Add(FGs2IdleAcquireActionListToEzAcquireActionList(v));
            }
            return r;
        }())
        ->WithIdlePeriodScheduleId(Model.IdlePeriodScheduleId)
        ->WithReceivePeriodScheduleId(Model.ReceivePeriodScheduleId);
}

UCLASS()
class BPGS2_API UGs2IdleCategoryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};