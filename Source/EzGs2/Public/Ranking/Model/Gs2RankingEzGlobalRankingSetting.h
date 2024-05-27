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
#include "Ranking/Model/GlobalRankingSetting.h"
#include "Gs2RankingEzScope.h"

namespace Gs2::UE5::Ranking::Model
{
	class EZGS2_API FEzGlobalRankingSetting final : public TSharedFromThis<FEzGlobalRankingSetting>
	{
        TOptional<int32> CalculateIntervalMinutesValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking::Model::FEzScope>>> AdditionalScopesValue;

	public:
        TSharedPtr<FEzGlobalRankingSetting> WithCalculateIntervalMinutes(const TOptional<int32> CalculateIntervalMinutes);
        TSharedPtr<FEzGlobalRankingSetting> WithAdditionalScopes(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking::Model::FEzScope>>> AdditionalScopes);

        TOptional<int32> GetCalculateIntervalMinutes() const;
        FString GetCalculateIntervalMinutesString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking::Model::FEzScope>>> GetAdditionalScopes() const;

        Gs2::Ranking::Model::FGlobalRankingSettingPtr ToModel() const;
        static TSharedPtr<FEzGlobalRankingSetting> FromModel(Gs2::Ranking::Model::FGlobalRankingSettingPtr Model);
    };
    typedef TSharedPtr<FEzGlobalRankingSetting> FEzGlobalRankingSettingPtr;
}