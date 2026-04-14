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
#include "FacetValueCount.h"
#include "NumericRange.h"

namespace Gs2::Log::Model
{
    class GS2LOG_API FFacet final : public FGs2Object, public TSharedFromThis<FFacet>
    {
        TOptional<FString> FieldValue;
        TSharedPtr<TArray<TSharedPtr<FFacetValueCount>>> ValuesValue;
        TSharedPtr<FNumericRange> RangeValue;
        TSharedPtr<FNumericRange> GlobalRangeValue;

    public:
        FFacet();
        FFacet(
            const FFacet& From
        );
        virtual ~FFacet() override = default;

        TSharedPtr<FFacet> WithField(const TOptional<FString> Field);
        TSharedPtr<FFacet> WithValues(const TSharedPtr<TArray<TSharedPtr<FFacetValueCount>>> Values);
        TSharedPtr<FFacet> WithRange(const TSharedPtr<FNumericRange> Range);
        TSharedPtr<FFacet> WithGlobalRange(const TSharedPtr<FNumericRange> GlobalRange);

        TOptional<FString> GetField() const;
        TSharedPtr<TArray<TSharedPtr<FFacetValueCount>>> GetValues() const;
        TSharedPtr<FNumericRange> GetRange() const;
        TSharedPtr<FNumericRange> GetGlobalRange() const;


        static TSharedPtr<FFacet> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFacet, ESPMode::ThreadSafe> FFacetPtr;
}