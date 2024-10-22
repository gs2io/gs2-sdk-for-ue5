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
#include "Dom/JsonObject.h"
#include "../Model/RepeatSetting.h"

namespace Gs2::Schedule::Request
{
    class FCreateEventMasterRequest;

    class GS2SCHEDULE_API FCreateEventMasterRequest final : public TSharedFromThis<FCreateEventMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScheduleTypeValue;
        TOptional<int64> AbsoluteBeginValue;
        TOptional<int64> AbsoluteEndValue;
        TOptional<FString> RepeatTypeValue;
        TOptional<int32> RepeatBeginDayOfMonthValue;
        TOptional<int32> RepeatEndDayOfMonthValue;
        TOptional<FString> RepeatBeginDayOfWeekValue;
        TOptional<FString> RepeatEndDayOfWeekValue;
        TOptional<int32> RepeatBeginHourValue;
        TOptional<int32> RepeatEndHourValue;
        TOptional<FString> RelativeTriggerNameValue;
        TSharedPtr<Model::FRepeatSetting> RepeatSettingValue;
        
    public:
        
        FCreateEventMasterRequest();
        FCreateEventMasterRequest(
            const FCreateEventMasterRequest& From
        );
        ~FCreateEventMasterRequest() = default;

        TSharedPtr<FCreateEventMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateEventMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateEventMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateEventMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateEventMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateEventMasterRequest> WithScheduleType(const TOptional<FString> ScheduleType);
        TSharedPtr<FCreateEventMasterRequest> WithAbsoluteBegin(const TOptional<int64> AbsoluteBegin);
        TSharedPtr<FCreateEventMasterRequest> WithAbsoluteEnd(const TOptional<int64> AbsoluteEnd);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatType(const TOptional<FString> RepeatType);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatBeginDayOfMonth(const TOptional<int32> RepeatBeginDayOfMonth);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatEndDayOfMonth(const TOptional<int32> RepeatEndDayOfMonth);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatBeginDayOfWeek(const TOptional<FString> RepeatBeginDayOfWeek);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatEndDayOfWeek(const TOptional<FString> RepeatEndDayOfWeek);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatBeginHour(const TOptional<int32> RepeatBeginHour);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatEndHour(const TOptional<int32> RepeatEndHour);
        TSharedPtr<FCreateEventMasterRequest> WithRelativeTriggerName(const TOptional<FString> RelativeTriggerName);
        TSharedPtr<FCreateEventMasterRequest> WithRepeatSetting(const TSharedPtr<Model::FRepeatSetting> RepeatSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetScheduleType() const;
        TOptional<int64> GetAbsoluteBegin() const;
        FString GetAbsoluteBeginString() const;
        TOptional<int64> GetAbsoluteEnd() const;
        FString GetAbsoluteEndString() const;
        TOptional<FString> GetRepeatType() const;
        TOptional<int32> GetRepeatBeginDayOfMonth() const;
        FString GetRepeatBeginDayOfMonthString() const;
        TOptional<int32> GetRepeatEndDayOfMonth() const;
        FString GetRepeatEndDayOfMonthString() const;
        TOptional<FString> GetRepeatBeginDayOfWeek() const;
        TOptional<FString> GetRepeatEndDayOfWeek() const;
        TOptional<int32> GetRepeatBeginHour() const;
        FString GetRepeatBeginHourString() const;
        TOptional<int32> GetRepeatEndHour() const;
        FString GetRepeatEndHourString() const;
        TOptional<FString> GetRelativeTriggerName() const;
        TSharedPtr<Model::FRepeatSetting> GetRepeatSetting() const;

        static TSharedPtr<FCreateEventMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequestPtr;
}