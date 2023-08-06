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
#include "Experience/Model/Status.h"

namespace Gs2::UE5::Experience::Model
{
	class EZGS2_API FEzStatus final : public TSharedFromThis<FEzStatus>
	{
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> ExperienceValueValue;
        TOptional<int64> RankValueValue;
        TOptional<int64> RankCapValueValue;
        TOptional<int64> NextRankUpExperienceValueValue;

	public:
        TSharedPtr<FEzStatus> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FEzStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FEzStatus> WithExperienceValue(const TOptional<int64> ExperienceValue);
        TSharedPtr<FEzStatus> WithRankValue(const TOptional<int64> RankValue);
        TSharedPtr<FEzStatus> WithRankCapValue(const TOptional<int64> RankCapValue);
        TSharedPtr<FEzStatus> WithNextRankUpExperienceValue(const TOptional<int64> NextRankUpExperienceValue);

        TOptional<FString> GetExperienceName() const;

        TOptional<FString> GetPropertyId() const;

        TOptional<int64> GetExperienceValue() const;
        FString GetExperienceValueString() const;

        TOptional<int64> GetRankValue() const;
        FString GetRankValueString() const;

        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;

        TOptional<int64> GetNextRankUpExperienceValue() const;
        FString GetNextRankUpExperienceValueString() const;

        Gs2::Experience::Model::FStatusPtr ToModel() const;
        static TSharedPtr<FEzStatus> FromModel(Gs2::Experience::Model::FStatusPtr Model);
    };
    typedef TSharedPtr<FEzStatus> FEzStatusPtr;
}