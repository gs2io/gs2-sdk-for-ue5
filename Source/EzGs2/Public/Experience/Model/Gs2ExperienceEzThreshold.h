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
#include "Experience/Model/Threshold.h"

namespace Gs2::UE5::Experience::Model
{
	class EZGS2_API FEzThreshold final : public TSharedFromThis<FEzThreshold>
	{
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<int64>> ValuesValue;

	public:
        TSharedPtr<FEzThreshold> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzThreshold> WithValues(const TSharedPtr<TArray<int64>> Values);

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<int64>> GetValues() const;

        Gs2::Experience::Model::FThresholdPtr ToModel() const;
        static TSharedPtr<FEzThreshold> FromModel(Gs2::Experience::Model::FThresholdPtr Model);
    };
    typedef TSharedPtr<FEzThreshold> FEzThresholdPtr;
}