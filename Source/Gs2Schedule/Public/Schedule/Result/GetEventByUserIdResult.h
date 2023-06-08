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
    class GS2SCHEDULE_API FGetEventByUserIdResult final : public TSharedFromThis<FGetEventByUserIdResult>
    {
        TSharedPtr<Model::FEvent> ItemValue;
        TOptional<int32> RepeatCountValue;
        TOptional<bool> InScheduleValue;
        TSharedPtr<Model::FRepeatSchedule> RepeatScheduleValue;
        
    public:
        
        FGetEventByUserIdResult();
        FGetEventByUserIdResult(
            const FGetEventByUserIdResult& From
        );
        ~FGetEventByUserIdResult() = default;

        TSharedPtr<FGetEventByUserIdResult> WithItem(const TSharedPtr<Model::FEvent> Item);
        TSharedPtr<FGetEventByUserIdResult> WithRepeatCount(const TOptional<int32> RepeatCount);
        TSharedPtr<FGetEventByUserIdResult> WithInSchedule(const TOptional<bool> InSchedule);
        TSharedPtr<FGetEventByUserIdResult> WithRepeatSchedule(const TSharedPtr<Model::FRepeatSchedule> RepeatSchedule);

        TSharedPtr<Model::FEvent> GetItem() const;
        TOptional<int32> GetRepeatCount() const;
        FString GetRepeatCountString() const;
        TOptional<bool> GetInSchedule() const;
        FString GetInScheduleString() const;
        TSharedPtr<Model::FRepeatSchedule> GetRepeatSchedule() const;

        static TSharedPtr<FGetEventByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEventByUserIdResult, ESPMode::ThreadSafe> FGetEventByUserIdResultPtr;
}