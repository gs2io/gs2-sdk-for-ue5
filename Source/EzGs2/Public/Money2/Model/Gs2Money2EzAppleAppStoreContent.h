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
#include "Money2/Model/AppleAppStoreContent.h"

namespace Gs2::UE5::Money2::Model
{
	class EZGS2_API FEzAppleAppStoreContent final : public TSharedFromThis<FEzAppleAppStoreContent>
	{
        TOptional<FString> ProductIdValue;

	public:
        TSharedPtr<FEzAppleAppStoreContent> WithProductId(const TOptional<FString> ProductId);

        TOptional<FString> GetProductId() const;

        Gs2::Money2::Model::FAppleAppStoreContentPtr ToModel() const;
        static TSharedPtr<FEzAppleAppStoreContent> FromModel(Gs2::Money2::Model::FAppleAppStoreContentPtr Model);
    };
    typedef TSharedPtr<FEzAppleAppStoreContent> FEzAppleAppStoreContentPtr;
}