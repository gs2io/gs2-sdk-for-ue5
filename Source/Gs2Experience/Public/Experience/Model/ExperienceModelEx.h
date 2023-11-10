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
#include "ExperienceModel.h"
#include "Status.h"

namespace Gs2::Experience::Model
{
	class GS2EXPERIENCE_API FExperienceModelEx
	{
	public:
		static int64 Rank(FExperienceModelPtr Model, FStatusPtr Status);

		static int64 NextRankExperienceValue(FExperienceModelPtr Model, FStatusPtr Status)
		{
			const auto NewRank = Rank(Model, Status);
			const auto MaxRank = Status->GetRankCapValue().IsSet() ? *Status->GetRankCapValue() : 0;
			if (NewRank == MaxRank)
			{
				return 0;
			}
			return (*Model->GetRankThreshold()->GetValues())[NewRank-1];
		}
	};
}