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

namespace Gs2::Schedule::Request
{
    class FUpdateEventMasterRequest;

    class GS2SCHEDULE_API FUpdateEventMasterRequest final : public TSharedFromThis<FUpdateEventMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> EventNameValue;
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
        
    public:
        
        FUpdateEventMasterRequest();
        FUpdateEventMasterRequest(
            const FUpdateEventMasterRequest& From
        );
        ~FUpdateEventMasterRequest() = default;

        TSharedPtr<FUpdateEventMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateEventMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateEventMasterRequest> WithEventName(const TOptional<FString> EventName);
        TSharedPtr<FUpdateEventMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateEventMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateEventMasterRequest> WithScheduleType(const TOptional<FString> ScheduleType);
        TSharedPtr<FUpdateEventMasterRequest> WithAbsoluteBegin(const TOptional<int64> AbsoluteBegin);
        TSharedPtr<FUpdateEventMasterRequest> WithAbsoluteEnd(const TOptional<int64> AbsoluteEnd);
        TSharedPtr<FUpdateEventMasterRequest> WithRepeatType(const TOptional<FString> RepeatType);
        TSharedPtr<FUpdateEventMasterRequest> WithRepeatBeginDayOfMonth(const TOptional<int32> RepeatBeginDayOfMonth);
        TSharedPtr<FUpdateEventMasterRequest> WithRepeatEndDayOfMonth(const TOptional<int32> RepeatEndDayOfMonth);
        TSharedPtr<FUpdateEventMasterRequest> WithRepeatBeginDayOfWeek(const TOptional<FString> RepeatBeginDayOfWeek);
        TSharedPtr<FUpdateEventMasterRequest> WithRepeatEndDayOfWeek(const TOptional<FString> RepeatEndDayOfWeek);
        TSharedPtr<FUpdateEventMasterRequest> WithRepeatBeginHour(const TOptional<int32> RepeatBeginHour);
        TSharedPtr<FUpdateEventMasterRequest> WithRepeatEndHour(const TOptional<int32> RepeatEndHour);
        TSharedPtr<FUpdateEventMasterRequest> WithRelativeTriggerName(const TOptional<FString> RelativeTriggerName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetEventName() const;
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

        static TSharedPtr<FUpdateEventMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateEventMasterRequest, ESPMode::ThreadSafe> FUpdateEventMasterRequestPtr;
}