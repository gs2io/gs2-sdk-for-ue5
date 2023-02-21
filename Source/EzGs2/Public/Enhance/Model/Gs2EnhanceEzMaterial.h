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
#include "Enhance/Model/Material.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzMaterial final : public TSharedFromThis<FEzMaterial>
	{
        TOptional<FString> MaterialItemSetIdValue;
        TOptional<int32> CountValue;

	public:
        TSharedPtr<FEzMaterial> WithMaterialItemSetId(const TOptional<FString> MaterialItemSetId);
        TSharedPtr<FEzMaterial> WithCount(const TOptional<int32> Count);

        TOptional<FString> GetMaterialItemSetId() const;

        TOptional<int32> GetCount() const;
        FString GetCountString() const;

        Gs2::Enhance::Model::FMaterialPtr ToModel() const;
        static TSharedPtr<FEzMaterial> FromModel(Gs2::Enhance::Model::FMaterialPtr Model);
    };
    typedef TSharedPtr<FEzMaterial> FEzMaterialPtr;
}