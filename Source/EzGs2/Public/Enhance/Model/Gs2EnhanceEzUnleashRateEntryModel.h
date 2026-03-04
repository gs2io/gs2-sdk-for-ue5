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
#include "Enhance/Model/UnleashRateEntryModel.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzUnleashRateEntryModel final : public TSharedFromThis<FEzUnleashRateEntryModel>
	{
        TOptional<int64> GradeValueValue;
        TOptional<int32> NeedCountValue;

	public:
        TSharedPtr<FEzUnleashRateEntryModel> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FEzUnleashRateEntryModel> WithNeedCount(const TOptional<int32> NeedCount);

        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;

        TOptional<int32> GetNeedCount() const;
        FString GetNeedCountString() const;

        Gs2::Enhance::Model::FUnleashRateEntryModelPtr ToModel() const;
        static TSharedPtr<FEzUnleashRateEntryModel> FromModel(Gs2::Enhance::Model::FUnleashRateEntryModelPtr Model);
    };
    typedef TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModelPtr;
}