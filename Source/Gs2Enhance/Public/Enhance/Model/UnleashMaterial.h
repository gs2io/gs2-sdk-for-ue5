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
#include "UnleashIndividualMaterialSetting.h"
#include "UnleashQuantityMaterialSetting.h"

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FUnleashMaterial final : public FGs2Object, public TSharedFromThis<FUnleashMaterial>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MaterialTypeValue;
        TSharedPtr<FUnleashIndividualMaterialSetting> IndividualSettingValue;
        TSharedPtr<FUnleashQuantityMaterialSetting> QuantitySettingValue;

    public:
        FUnleashMaterial();
        FUnleashMaterial(
            const FUnleashMaterial& From
        );
        virtual ~FUnleashMaterial() override = default;

        TSharedPtr<FUnleashMaterial> WithName(const TOptional<FString> Name);
        TSharedPtr<FUnleashMaterial> WithMaterialType(const TOptional<FString> MaterialType);
        TSharedPtr<FUnleashMaterial> WithIndividualSetting(const TSharedPtr<FUnleashIndividualMaterialSetting> IndividualSetting);
        TSharedPtr<FUnleashMaterial> WithQuantitySetting(const TSharedPtr<FUnleashQuantityMaterialSetting> QuantitySetting);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMaterialType() const;
        TSharedPtr<FUnleashIndividualMaterialSetting> GetIndividualSetting() const;
        TSharedPtr<FUnleashQuantityMaterialSetting> GetQuantitySetting() const;


        static TSharedPtr<FUnleashMaterial> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashMaterial, ESPMode::ThreadSafe> FUnleashMaterialPtr;
}