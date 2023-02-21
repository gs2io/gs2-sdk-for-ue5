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
#include "Matchmaking/Model/Attribute.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzAttribute final : public TSharedFromThis<FEzAttribute>
	{
        TOptional<FString> NameValue;
        TOptional<int32> ValueValue;

	public:
        TSharedPtr<FEzAttribute> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzAttribute> WithValue(const TOptional<int32> Value);

        TOptional<FString> GetName() const;

        TOptional<int32> GetValue() const;
        FString GetValueString() const;

        Gs2::Matchmaking::Model::FAttributePtr ToModel() const;
        static TSharedPtr<FEzAttribute> FromModel(Gs2::Matchmaking::Model::FAttributePtr Model);
    };
    typedef TSharedPtr<FEzAttribute> FEzAttributePtr;
}