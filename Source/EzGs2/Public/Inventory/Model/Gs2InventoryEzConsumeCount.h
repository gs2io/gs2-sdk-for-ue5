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
#include "Inventory/Model/ConsumeCount.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzConsumeCount final : public TSharedFromThis<FEzConsumeCount>
	{
        TOptional<FString> ItemNameValue;
        TOptional<int64> CountValue;

	public:
        TSharedPtr<FEzConsumeCount> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FEzConsumeCount> WithCount(const TOptional<int64> Count);

        TOptional<FString> GetItemName() const;

        TOptional<int64> GetCount() const;
        FString GetCountString() const;

        Gs2::Inventory::Model::FConsumeCountPtr ToModel() const;
        static TSharedPtr<FEzConsumeCount> FromModel(Gs2::Inventory::Model::FConsumeCountPtr Model);
    };
    typedef TSharedPtr<FEzConsumeCount> FEzConsumeCountPtr;
}