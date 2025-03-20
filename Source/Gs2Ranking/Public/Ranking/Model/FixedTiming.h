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

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FFixedTiming final : public FGs2Object, public TSharedFromThis<FFixedTiming>
    {
        TOptional<int32> HourValue;
        TOptional<int32> MinuteValue;

    public:
        FFixedTiming();
        FFixedTiming(
            const FFixedTiming& From
        );
        virtual ~FFixedTiming() override = default;

        TSharedPtr<FFixedTiming> WithHour(const TOptional<int32> Hour);
        TSharedPtr<FFixedTiming> WithMinute(const TOptional<int32> Minute);

        TOptional<int32> GetHour() const;
        FString GetHourString() const;
        TOptional<int32> GetMinute() const;
        FString GetMinuteString() const;


        static TSharedPtr<FFixedTiming> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFixedTiming, ESPMode::ThreadSafe> FFixedTimingPtr;
}