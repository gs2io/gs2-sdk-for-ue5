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

namespace Gs2::Log::Model
{
    class GS2LOG_API FTimeseriesValue final : public FGs2Object, public TSharedFromThis<FTimeseriesValue>
    {
        TOptional<FString> KeyValue;
        TOptional<double> ValueValue;

    public:
        FTimeseriesValue();
        FTimeseriesValue(
            const FTimeseriesValue& From
        );
        virtual ~FTimeseriesValue() override = default;

        TSharedPtr<FTimeseriesValue> WithKey(const TOptional<FString> Key);
        TSharedPtr<FTimeseriesValue> WithValue(const TOptional<double> Value);

        TOptional<FString> GetKey() const;
        TOptional<double> GetValue() const;
        FString GetValueString() const;


        static TSharedPtr<FTimeseriesValue> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTimeseriesValue, ESPMode::ThreadSafe> FTimeseriesValuePtr;
}