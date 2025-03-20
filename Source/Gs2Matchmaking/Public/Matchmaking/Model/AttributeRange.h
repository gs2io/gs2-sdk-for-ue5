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
    class GS2MATCHMAKING_API FAttributeRange final : public FGs2Object, public TSharedFromThis<FAttributeRange>
    {
        TOptional<FString> NameValue;
        TOptional<int32> MinValue;
        TOptional<int32> MaxValue;

    public:
        FAttributeRange();
        FAttributeRange(
            const FAttributeRange& From
        );
        virtual ~FAttributeRange() override = default;

        TSharedPtr<FAttributeRange> WithName(const TOptional<FString> Name);
        TSharedPtr<FAttributeRange> WithMin(const TOptional<int32> Min);
        TSharedPtr<FAttributeRange> WithMax(const TOptional<int32> Max);

        TOptional<FString> GetName() const;
        TOptional<int32> GetMin() const;
        FString GetMinString() const;
        TOptional<int32> GetMax() const;
        FString GetMaxString() const;


        static TSharedPtr<FAttributeRange> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAttributeRange, ESPMode::ThreadSafe> FAttributeRangePtr;
}