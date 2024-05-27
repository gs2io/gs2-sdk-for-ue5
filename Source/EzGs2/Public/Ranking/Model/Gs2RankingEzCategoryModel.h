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
#include "Ranking/Model/CategoryModel.h"
#include "Gs2RankingEzGlobalRankingSetting.h"

namespace Gs2::UE5::Ranking::Model
{
	class EZGS2_API FEzCategoryModel final : public TSharedFromThis<FEzCategoryModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<Gs2::UE5::Ranking::Model::FEzGlobalRankingSetting> GlobalRankingSettingValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;

	public:
        TSharedPtr<FEzCategoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzCategoryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzCategoryModel> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FEzCategoryModel> WithGlobalRankingSetting(const TSharedPtr<Gs2::UE5::Ranking::Model::FEzGlobalRankingSetting> GlobalRankingSetting);
        TSharedPtr<FEzCategoryModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FEzCategoryModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetScope() const;

        TSharedPtr<Gs2::UE5::Ranking::Model::FEzGlobalRankingSetting> GetGlobalRankingSetting() const;

        TOptional<FString> GetEntryPeriodEventId() const;

        TOptional<FString> GetAccessPeriodEventId() const;

        Gs2::Ranking::Model::FCategoryModelPtr ToModel() const;
        static TSharedPtr<FEzCategoryModel> FromModel(Gs2::Ranking::Model::FCategoryModelPtr Model);
    };
    typedef TSharedPtr<FEzCategoryModel> FEzCategoryModelPtr;
}