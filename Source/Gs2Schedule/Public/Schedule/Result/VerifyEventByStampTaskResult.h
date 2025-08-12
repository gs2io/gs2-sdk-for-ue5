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
#include "../Model/Event.h"
#include "../Model/RepeatSchedule.h"

namespace Gs2::Schedule::Result
{
    class GS2SCHEDULE_API FVerifyEventByStampTaskResult final : public TSharedFromThis<FVerifyEventByStampTaskResult>
    {
        TSharedPtr<Model::FEvent> ItemValue;
        TOptional<bool> InScheduleValue;
        TOptional<int64> ScheduleStartAtValue;
        TOptional<int64> ScheduleEndAtValue;
        TSharedPtr<Model::FRepeatSchedule> RepeatScheduleValue;
        TOptional<bool> IsGlobalScheduleValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FVerifyEventByStampTaskResult();
        FVerifyEventByStampTaskResult(
            const FVerifyEventByStampTaskResult& From
        );
        ~FVerifyEventByStampTaskResult() = default;

        TSharedPtr<FVerifyEventByStampTaskResult> WithItem(const TSharedPtr<Model::FEvent> Item);
        TSharedPtr<FVerifyEventByStampTaskResult> WithInSchedule(const TOptional<bool> InSchedule);
        TSharedPtr<FVerifyEventByStampTaskResult> WithScheduleStartAt(const TOptional<int64> ScheduleStartAt);
        TSharedPtr<FVerifyEventByStampTaskResult> WithScheduleEndAt(const TOptional<int64> ScheduleEndAt);
        TSharedPtr<FVerifyEventByStampTaskResult> WithRepeatSchedule(const TSharedPtr<Model::FRepeatSchedule> RepeatSchedule);
        TSharedPtr<FVerifyEventByStampTaskResult> WithIsGlobalSchedule(const TOptional<bool> IsGlobalSchedule);
        TSharedPtr<FVerifyEventByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FEvent> GetItem() const;
        TOptional<bool> GetInSchedule() const;
        FString GetInScheduleString() const;
        TOptional<int64> GetScheduleStartAt() const;
        FString GetScheduleStartAtString() const;
        TOptional<int64> GetScheduleEndAt() const;
        FString GetScheduleEndAtString() const;
        TSharedPtr<Model::FRepeatSchedule> GetRepeatSchedule() const;
        TOptional<bool> GetIsGlobalSchedule() const;
        FString GetIsGlobalScheduleString() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FVerifyEventByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyEventByStampTaskResult, ESPMode::ThreadSafe> FVerifyEventByStampTaskResultPtr;
}