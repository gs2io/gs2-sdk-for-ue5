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
#include "Matchmaking/Model/AttributeRange.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzAttributeRange final : public TSharedFromThis<FEzAttributeRange>
	{
        TOptional<FString> NameValue;
        TOptional<int32> MinValue;
        TOptional<int32> MaxValue;

	public:
        TSharedPtr<FEzAttributeRange> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzAttributeRange> WithMin(const TOptional<int32> Min);
        TSharedPtr<FEzAttributeRange> WithMax(const TOptional<int32> Max);

        TOptional<FString> GetName() const;

        TOptional<int32> GetMin() const;
        FString GetMinString() const;

        TOptional<int32> GetMax() const;
        FString GetMaxString() const;

        Gs2::Matchmaking::Model::FAttributeRangePtr ToModel() const;
        static TSharedPtr<FEzAttributeRange> FromModel(Gs2::Matchmaking::Model::FAttributeRangePtr Model);
    };
    typedef TSharedPtr<FEzAttributeRange> FEzAttributeRangePtr;
}