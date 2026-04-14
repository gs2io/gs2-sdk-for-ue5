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
    class GS2LOG_API FFacetValueCount final : public FGs2Object, public TSharedFromThis<FFacetValueCount>
    {
        TOptional<FString> ValueValue;
        TOptional<int64> CountValue;

    public:
        FFacetValueCount();
        FFacetValueCount(
            const FFacetValueCount& From
        );
        virtual ~FFacetValueCount() override = default;

        TSharedPtr<FFacetValueCount> WithValue(const TOptional<FString> Value);
        TSharedPtr<FFacetValueCount> WithCount(const TOptional<int64> Count);

        TOptional<FString> GetValue() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FFacetValueCount> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFacetValueCount, ESPMode::ThreadSafe> FFacetValueCountPtr;
}