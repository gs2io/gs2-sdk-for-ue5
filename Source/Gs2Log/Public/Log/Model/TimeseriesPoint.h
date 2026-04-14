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
#include "TimeseriesValue.h"

namespace Gs2::Log::Model
{
    class GS2LOG_API FTimeseriesPoint final : public FGs2Object, public TSharedFromThis<FTimeseriesPoint>
    {
        TOptional<int64> TimestampValue;
        TSharedPtr<TArray<TSharedPtr<FTimeseriesValue>>> ValuesValue;

    public:
        FTimeseriesPoint();
        FTimeseriesPoint(
            const FTimeseriesPoint& From
        );
        virtual ~FTimeseriesPoint() override = default;

        TSharedPtr<FTimeseriesPoint> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FTimeseriesPoint> WithValues(const TSharedPtr<TArray<TSharedPtr<FTimeseriesValue>>> Values);

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TSharedPtr<TArray<TSharedPtr<FTimeseriesValue>>> GetValues() const;


        static TSharedPtr<FTimeseriesPoint> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTimeseriesPoint, ESPMode::ThreadSafe> FTimeseriesPointPtr;
}