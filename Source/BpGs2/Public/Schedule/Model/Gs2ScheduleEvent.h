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
#include "Schedule/Domain/Model/Gs2ScheduleEzEventGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ScheduleEvent.generated.h"

USTRUCT(BlueprintType)
struct FGs2ScheduleOwnEvent
{
    GENERATED_BODY()

    Gs2::UE5::Schedule::Domain::Model::FEzEventGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ScheduleEventValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ScheduleType = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RepeatType = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 AbsoluteBegin = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 AbsoluteEnd = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 RepeatBeginDayOfMonth = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 RepeatEndDayOfMonth = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RepeatBeginDayOfWeek = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RepeatEndDayOfWeek = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 RepeatBeginHour = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 RepeatEndHour = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RelativeTriggerName = "";
};

inline FGs2ScheduleEventValue EzEventToFGs2ScheduleEventValue(
    const Gs2::UE5::Schedule::Model::FEzEventPtr Model
)
{
    FGs2ScheduleEventValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleEventFunctionLibrary::EzEventToFGs2ScheduleEventValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ScheduleType = Model->GetScheduleType() ? *Model->GetScheduleType() : "";
    Value.RepeatType = Model->GetRepeatType() ? *Model->GetRepeatType() : "";
    Value.AbsoluteBegin = Model->GetAbsoluteBegin() ? *Model->GetAbsoluteBegin() : 0;
    Value.AbsoluteEnd = Model->GetAbsoluteEnd() ? *Model->GetAbsoluteEnd() : 0;
    Value.RepeatBeginDayOfMonth = Model->GetRepeatBeginDayOfMonth() ? *Model->GetRepeatBeginDayOfMonth() : 0;
    Value.RepeatEndDayOfMonth = Model->GetRepeatEndDayOfMonth() ? *Model->GetRepeatEndDayOfMonth() : 0;
    Value.RepeatBeginDayOfWeek = Model->GetRepeatBeginDayOfWeek() ? *Model->GetRepeatBeginDayOfWeek() : "";
    Value.RepeatEndDayOfWeek = Model->GetRepeatEndDayOfWeek() ? *Model->GetRepeatEndDayOfWeek() : "";
    Value.RepeatBeginHour = Model->GetRepeatBeginHour() ? *Model->GetRepeatBeginHour() : 0;
    Value.RepeatEndHour = Model->GetRepeatEndHour() ? *Model->GetRepeatEndHour() : 0;
    Value.RelativeTriggerName = Model->GetRelativeTriggerName() ? *Model->GetRelativeTriggerName() : "";
    return Value;
}

inline Gs2::UE5::Schedule::Model::FEzEventPtr FGs2ScheduleEventValueToEzEvent(
    const FGs2ScheduleEventValue Model
)
{
    return MakeShared<Gs2::UE5::Schedule::Model::FEzEvent>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithScheduleType(Model.ScheduleType)
        ->WithRepeatType(Model.RepeatType)
        ->WithAbsoluteBegin(Model.AbsoluteBegin)
        ->WithAbsoluteEnd(Model.AbsoluteEnd)
        ->WithRepeatBeginDayOfMonth(Model.RepeatBeginDayOfMonth)
        ->WithRepeatEndDayOfMonth(Model.RepeatEndDayOfMonth)
        ->WithRepeatBeginDayOfWeek(Model.RepeatBeginDayOfWeek)
        ->WithRepeatEndDayOfWeek(Model.RepeatEndDayOfWeek)
        ->WithRepeatBeginHour(Model.RepeatBeginHour)
        ->WithRepeatEndHour(Model.RepeatEndHour)
        ->WithRelativeTriggerName(Model.RelativeTriggerName);
}

UCLASS()
class BPGS2_API UGs2ScheduleEventFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};