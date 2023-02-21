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
#include "Stamina/Model/MaxStaminaTable.h"

namespace Gs2::UE5::Stamina::Model
{
	class EZGS2_API FEzMaxStaminaTable final : public TSharedFromThis<FEzMaxStaminaTable>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<int32>> ValuesValue;

	public:
        TSharedPtr<FEzMaxStaminaTable> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzMaxStaminaTable> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzMaxStaminaTable> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FEzMaxStaminaTable> WithValues(const TSharedPtr<TArray<int32>> Values);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetExperienceModelId() const;

        TSharedPtr<TArray<int32>> GetValues() const;

        Gs2::Stamina::Model::FMaxStaminaTablePtr ToModel() const;
        static TSharedPtr<FEzMaxStaminaTable> FromModel(Gs2::Stamina::Model::FMaxStaminaTablePtr Model);
    };
    typedef TSharedPtr<FEzMaxStaminaTable> FEzMaxStaminaTablePtr;
}