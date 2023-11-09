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
#include "Mission/Domain/Model/Gs2MissionEzMissionGroupModelDomain.h"
#include "Mission/Model/Gs2MissionMissionTaskModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MissionMissionGroupModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionMissionGroupModel
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::Model::FEzMissionGroupModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MissionMissionGroupModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2MissionMissionTaskModelValue> Tasks = TArray<FGs2MissionMissionTaskModelValue>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ResetType = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 ResetDayOfMonth = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ResetDayOfWeek = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 ResetHour = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString CompleteNotificationNamespaceId = "";
};

inline FGs2MissionMissionGroupModelValue EzMissionGroupModelToFGs2MissionMissionGroupModelValue(
    const Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr Model
)
{
    FGs2MissionMissionGroupModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionMissionGroupModelFunctionLibrary::EzMissionGroupModelToFGs2MissionMissionGroupModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Tasks = Model->GetTasks() ? [&]
    {
        TArray<FGs2MissionMissionTaskModelValue> r;
        for (auto v : *Model->GetTasks())
        {
            r.Add(EzMissionTaskModelToFGs2MissionMissionTaskModelValue(v));
        }
        return r;
    }() : TArray<FGs2MissionMissionTaskModelValue>();
    Value.ResetType = Model->GetResetType() ? *Model->GetResetType() : "";
    Value.ResetDayOfMonth = Model->GetResetDayOfMonth() ? *Model->GetResetDayOfMonth() : 0;
    Value.ResetDayOfWeek = Model->GetResetDayOfWeek() ? *Model->GetResetDayOfWeek() : "";
    Value.ResetHour = Model->GetResetHour() ? *Model->GetResetHour() : 0;
    Value.CompleteNotificationNamespaceId = Model->GetCompleteNotificationNamespaceId() ? *Model->GetCompleteNotificationNamespaceId() : "";
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr FGs2MissionMissionGroupModelValueToEzMissionGroupModel(
    const FGs2MissionMissionGroupModelValue Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzMissionGroupModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTasks([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr>>();
            for (auto v : Model.Tasks) {
                r->Add(FGs2MissionMissionTaskModelValueToEzMissionTaskModel(v));
            }
            return r;
        }())
        ->WithResetType(Model.ResetType)
        ->WithResetDayOfMonth(Model.ResetDayOfMonth)
        ->WithResetDayOfWeek(Model.ResetDayOfWeek)
        ->WithResetHour(Model.ResetHour)
        ->WithCompleteNotificationNamespaceId(Model.CompleteNotificationNamespaceId);
}

UCLASS()
class BPGS2_API UGs2MissionMissionGroupModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::MissionTaskModel", Category="Game Server Services|GS2-Mission|Namespace|MissionGroupModel|MissionTaskModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="MissionTaskModel") FGs2MissionMissionTaskModel MissionTaskModel(
        FGs2MissionMissionGroupModel MissionGroupModel,
        FString MissionTaskName
    );
};