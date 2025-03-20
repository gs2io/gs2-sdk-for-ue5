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
#include "DrawnPrize.h"

namespace Gs2::Lottery::Model
{
    class GS2LOTTERY_API FProbability final : public FGs2Object, public TSharedFromThis<FProbability>
    {
        TSharedPtr<FDrawnPrize> PrizeValue;
        TOptional<float> RateValue;

    public:
        FProbability();
        FProbability(
            const FProbability& From
        );
        virtual ~FProbability() override = default;

        TSharedPtr<FProbability> WithPrize(const TSharedPtr<FDrawnPrize> Prize);
        TSharedPtr<FProbability> WithRate(const TOptional<float> Rate);

        TSharedPtr<FDrawnPrize> GetPrize() const;
        TOptional<float> GetRate() const;
        FString GetRateString() const;


        static TSharedPtr<FProbability> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FProbability, ESPMode::ThreadSafe> FProbabilityPtr;
}