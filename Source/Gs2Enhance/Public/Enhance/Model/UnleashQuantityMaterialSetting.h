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
    class GS2ENHANCE_API FUnleashQuantityMaterialSetting final : public FGs2Object, public TSharedFromThis<FUnleashQuantityMaterialSetting>
    {
        TOptional<FString> MatchTypeValue;
        TOptional<FString> MaterialInventoryModelIdValue;
        TOptional<FString> ItemModelIdValue;
        TOptional<int32> CountValue;

    public:
        FUnleashQuantityMaterialSetting();
        FUnleashQuantityMaterialSetting(
            const FUnleashQuantityMaterialSetting& From
        );
        virtual ~FUnleashQuantityMaterialSetting() override = default;

        TSharedPtr<FUnleashQuantityMaterialSetting> WithMatchType(const TOptional<FString> MatchType);
        TSharedPtr<FUnleashQuantityMaterialSetting> WithMaterialInventoryModelId(const TOptional<FString> MaterialInventoryModelId);
        TSharedPtr<FUnleashQuantityMaterialSetting> WithItemModelId(const TOptional<FString> ItemModelId);
        TSharedPtr<FUnleashQuantityMaterialSetting> WithCount(const TOptional<int32> Count);

        TOptional<FString> GetMatchType() const;
        TOptional<FString> GetMaterialInventoryModelId() const;
        TOptional<FString> GetItemModelId() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FUnleashQuantityMaterialSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashQuantityMaterialSetting, ESPMode::ThreadSafe> FUnleashQuantityMaterialSettingPtr;
}