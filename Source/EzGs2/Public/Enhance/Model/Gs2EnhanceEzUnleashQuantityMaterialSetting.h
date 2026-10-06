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
#include "Enhance/Model/UnleashQuantityMaterialSetting.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzUnleashQuantityMaterialSetting final : public TSharedFromThis<FEzUnleashQuantityMaterialSetting>
	{
        TOptional<FString> MatchTypeValue;
        TOptional<FString> MaterialInventoryModelIdValue;
        TOptional<FString> ItemModelIdValue;
        TOptional<int32> CountValue;

	public:
        TSharedPtr<FEzUnleashQuantityMaterialSetting> WithMatchType(const TOptional<FString> MatchType);
        TSharedPtr<FEzUnleashQuantityMaterialSetting> WithMaterialInventoryModelId(const TOptional<FString> MaterialInventoryModelId);
        TSharedPtr<FEzUnleashQuantityMaterialSetting> WithItemModelId(const TOptional<FString> ItemModelId);
        TSharedPtr<FEzUnleashQuantityMaterialSetting> WithCount(const TOptional<int32> Count);

        TOptional<FString> GetMatchType() const;

        TOptional<FString> GetMaterialInventoryModelId() const;

        TOptional<FString> GetItemModelId() const;

        TOptional<int32> GetCount() const;
        FString GetCountString() const;

        Gs2::Enhance::Model::FUnleashQuantityMaterialSettingPtr ToModel() const;
        static TSharedPtr<FEzUnleashQuantityMaterialSetting> FromModel(Gs2::Enhance::Model::FUnleashQuantityMaterialSettingPtr Model);
    };
    typedef TSharedPtr<FEzUnleashQuantityMaterialSetting> FEzUnleashQuantityMaterialSettingPtr;
}