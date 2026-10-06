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
#include "Core/Gs2Object.h"

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FUnleashIndividualMaterialSetting final : public FGs2Object, public TSharedFromThis<FUnleashIndividualMaterialSetting>
    {
        TOptional<FString> MatchTypeValue;
        TOptional<FString> GradeConditionValue;
        TOptional<int64> GradeValueValue;
        TOptional<int32> CountValue;

    public:
        FUnleashIndividualMaterialSetting();
        FUnleashIndividualMaterialSetting(
            const FUnleashIndividualMaterialSetting& From
        );
        virtual ~FUnleashIndividualMaterialSetting() override = default;

        TSharedPtr<FUnleashIndividualMaterialSetting> WithMatchType(const TOptional<FString> MatchType);
        TSharedPtr<FUnleashIndividualMaterialSetting> WithGradeCondition(const TOptional<FString> GradeCondition);
        TSharedPtr<FUnleashIndividualMaterialSetting> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FUnleashIndividualMaterialSetting> WithCount(const TOptional<int32> Count);

        TOptional<FString> GetMatchType() const;
        TOptional<FString> GetGradeCondition() const;
        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FUnleashIndividualMaterialSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashIndividualMaterialSetting, ESPMode::ThreadSafe> FUnleashIndividualMaterialSettingPtr;
}