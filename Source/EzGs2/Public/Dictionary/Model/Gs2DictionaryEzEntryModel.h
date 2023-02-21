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
#include "Dictionary/Model/EntryModel.h"

namespace Gs2::UE5::Dictionary::Model
{
	class EZGS2_API FEzEntryModel final : public TSharedFromThis<FEzEntryModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;

	public:
        TSharedPtr<FEzEntryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzEntryModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        Gs2::Dictionary::Model::FEntryModelPtr ToModel() const;
        static TSharedPtr<FEzEntryModel> FromModel(Gs2::Dictionary::Model::FEntryModelPtr Model);
    };
    typedef TSharedPtr<FEzEntryModel> FEzEntryModelPtr;
}