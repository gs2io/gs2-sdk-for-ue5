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
#include "Enhance/Model/UnleashIndividualMaterialSetting.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzUnleashIndividualMaterialSetting final : public TSharedFromThis<FEzUnleashIndividualMaterialSetting>
	{
        TOptional<FString> MatchTypeValue;
        TOptional<FString> GradeConditionValue;
        TOptional<int64> GradeValueValue;
        TOptional<int32> CountValue;

	public:
        TSharedPtr<FEzUnleashIndividualMaterialSetting> WithMatchType(const TOptional<FString> MatchType);
        TSharedPtr<FEzUnleashIndividualMaterialSetting> WithGradeCondition(const TOptional<FString> GradeCondition);
        TSharedPtr<FEzUnleashIndividualMaterialSetting> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FEzUnleashIndividualMaterialSetting> WithCount(const TOptional<int32> Count);

        TOptional<FString> GetMatchType() const;

        TOptional<FString> GetGradeCondition() const;

        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;

        TOptional<int32> GetCount() const;
        FString GetCountString() const;

        Gs2::Enhance::Model::FUnleashIndividualMaterialSettingPtr ToModel() const;
        static TSharedPtr<FEzUnleashIndividualMaterialSetting> FromModel(Gs2::Enhance::Model::FUnleashIndividualMaterialSettingPtr Model);
    };
    typedef TSharedPtr<FEzUnleashIndividualMaterialSetting> FEzUnleashIndividualMaterialSettingPtr;
}