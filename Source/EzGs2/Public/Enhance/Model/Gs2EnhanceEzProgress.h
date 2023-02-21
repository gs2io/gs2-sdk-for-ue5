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
#include "Enhance/Model/Progress.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzProgress final : public TSharedFromThis<FEzProgress>
	{
        TOptional<FString> NameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int32> ExperienceValueValue;
        TOptional<float> RateValue;

	public:
        TSharedPtr<FEzProgress> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzProgress> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FEzProgress> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FEzProgress> WithExperienceValue(const TOptional<int32> ExperienceValue);
        TSharedPtr<FEzProgress> WithRate(const TOptional<float> Rate);

        TOptional<FString> GetName() const;

        TOptional<FString> GetRateName() const;

        TOptional<FString> GetPropertyId() const;

        TOptional<int32> GetExperienceValue() const;
        FString GetExperienceValueString() const;

        TOptional<float> GetRate() const;
        FString GetRateString() const;

        Gs2::Enhance::Model::FProgressPtr ToModel() const;
        static TSharedPtr<FEzProgress> FromModel(Gs2::Enhance::Model::FProgressPtr Model);
    };
    typedef TSharedPtr<FEzProgress> FEzProgressPtr;
}