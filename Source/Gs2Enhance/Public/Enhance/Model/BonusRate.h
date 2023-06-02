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

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FBonusRate final : public Gs2Object, public TSharedFromThis<FBonusRate>
    {
        TOptional<float> RateValue;
        TOptional<int32> WeightValue;

    public:
        FBonusRate();
        FBonusRate(
            const FBonusRate& From
        );
        virtual ~FBonusRate() override = default;

        TSharedPtr<FBonusRate> WithRate(const TOptional<float> Rate);
        TSharedPtr<FBonusRate> WithWeight(const TOptional<int32> Weight);

        TOptional<float> GetRate() const;
        FString GetRateString() const;
        TOptional<int32> GetWeight() const;
        FString GetWeightString() const;


        static TSharedPtr<FBonusRate> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBonusRate, ESPMode::ThreadSafe> FBonusRatePtr;
}