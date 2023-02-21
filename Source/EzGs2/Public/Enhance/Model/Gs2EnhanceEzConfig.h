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
#include "Enhance/Model/Config.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzConfig final : public TSharedFromThis<FEzConfig>
	{
        TOptional<FString> KeyValue;
        TOptional<FString> ValueValue;

	public:
        TSharedPtr<FEzConfig> WithKey(const TOptional<FString> Key);
        TSharedPtr<FEzConfig> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetKey() const;

        TOptional<FString> GetValue() const;

        Gs2::Enhance::Model::FConfigPtr ToModel() const;
        static TSharedPtr<FEzConfig> FromModel(Gs2::Enhance::Model::FConfigPtr Model);
    };
    typedef TSharedPtr<FEzConfig> FEzConfigPtr;
}