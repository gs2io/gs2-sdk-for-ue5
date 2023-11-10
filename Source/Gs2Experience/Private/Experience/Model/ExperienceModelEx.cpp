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

#include "Experience/Model/ExperienceModelEx.h"

namespace Gs2::Experience::Model
{
	int64 FExperienceModelEx::Rank(FExperienceModelPtr Model, FStatusPtr Status)
	{
		if (!Model.IsValid())
		{
			return 0;
		}
		const auto Rank = Model->GetRankThreshold()->GetValues()->FilterByPredicate([Status](int64 V)
		{
			if (!Status.IsValid())
			{
				return false;
			}
			const auto ExperienceValue = Status->GetExperienceValue().IsSet() ? *Status->GetExperienceValue() : 0;
			return V < ExperienceValue;
		}).Num() + 1;
		const auto MaxRank = Status->GetRankCapValue().IsSet() ? *Status->GetRankCapValue() : 0;
		return FMath::Min(Rank, MaxRank);
	}
}
