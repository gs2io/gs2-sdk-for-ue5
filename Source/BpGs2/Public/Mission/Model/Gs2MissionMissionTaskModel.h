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
#include "Mission/Domain/Model/Gs2MissionEzMissionTaskModelDomain.h"
#include "Mission/Model/Gs2MissionAcquireAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MissionMissionTaskModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionMissionTaskModel
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::Model::FEzMissionTaskModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MissionMissionTaskModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    FString CounterName = "";
    UPROPERTY(BlueprintReadOnly)
    int64 TargetValue = 0;
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2MissionAcquireAction> CompleteAcquireActions = TArray<FGs2MissionAcquireAction>();
    UPROPERTY(BlueprintReadOnly)
    FString ChallengePeriodEventId = "";
    UPROPERTY(BlueprintReadOnly)
    FString PremiseMissionTaskName = "";
};

inline FGs2MissionMissionTaskModelValue EzMissionTaskModelToFGs2MissionMissionTaskModelValue(
    const Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr Model
)
{
    FGs2MissionMissionTaskModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionMissionTaskModelFunctionLibrary::EzMissionTaskModelToFGs2MissionMissionTaskModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.CounterName = Model->GetCounterName() ? *Model->GetCounterName() : "";
    Value.TargetValue = Model->GetTargetValue() ? *Model->GetTargetValue() : 0;
    Value.CompleteAcquireActions = Model->GetCompleteAcquireActions() ? [&]
    {
        TArray<FGs2MissionAcquireAction> r;
        for (auto v : *Model->GetCompleteAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2MissionAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2MissionAcquireAction>();
    Value.ChallengePeriodEventId = Model->GetChallengePeriodEventId() ? *Model->GetChallengePeriodEventId() : "";
    Value.PremiseMissionTaskName = Model->GetPremiseMissionTaskName() ? *Model->GetPremiseMissionTaskName() : "";
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr FGs2MissionMissionTaskModelValueToEzMissionTaskModel(
    const FGs2MissionMissionTaskModelValue Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzMissionTaskModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithCounterName(Model.CounterName)
        ->WithTargetValue(Model.TargetValue)
        ->WithCompleteAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Mission::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.CompleteAcquireActions) {
                r->Add(FGs2MissionAcquireActionToEzAcquireAction(v));
            }
            return r;
        }())
        ->WithChallengePeriodEventId(Model.ChallengePeriodEventId)
        ->WithPremiseMissionTaskName(Model.PremiseMissionTaskName);
}

UCLASS()
class BPGS2_API UGs2MissionMissionTaskModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};