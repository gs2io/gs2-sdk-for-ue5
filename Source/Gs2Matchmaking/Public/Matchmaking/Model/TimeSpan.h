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
#include "Core/Gs2Object.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FTimeSpan final : public FGs2Object, public TSharedFromThis<FTimeSpan>
    {
        TOptional<int32> DaysValue;
        TOptional<int32> HoursValue;
        TOptional<int32> MinutesValue;

    public:
        FTimeSpan();
        FTimeSpan(
            const FTimeSpan& From
        );
        virtual ~FTimeSpan() override = default;

        TSharedPtr<FTimeSpan> WithDays(const TOptional<int32> Days);
        TSharedPtr<FTimeSpan> WithHours(const TOptional<int32> Hours);
        TSharedPtr<FTimeSpan> WithMinutes(const TOptional<int32> Minutes);

        TOptional<int32> GetDays() const;
        FString GetDaysString() const;
        TOptional<int32> GetHours() const;
        FString GetHoursString() const;
        TOptional<int32> GetMinutes() const;
        FString GetMinutesString() const;


        static TSharedPtr<FTimeSpan> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTimeSpan, ESPMode::ThreadSafe> FTimeSpanPtr;
}