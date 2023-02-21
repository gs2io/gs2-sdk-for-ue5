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
#include "Mission/Model/Counter.h"
#include "Gs2MissionEzScopedValue.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzCounter final : public TSharedFromThis<FEzCounter>
	{
        TOptional<FString> NameValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzScopedValue>>> ValuesValue;

	public:
        TSharedPtr<FEzCounter> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzCounter> WithValues(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzScopedValue>>> Values);

        TOptional<FString> GetName() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzScopedValue>>> GetValues() const;

        Gs2::Mission::Model::FCounterPtr ToModel() const;
        static TSharedPtr<FEzCounter> FromModel(Gs2::Mission::Model::FCounterPtr Model);
    };
    typedef TSharedPtr<FEzCounter> FEzCounterPtr;
}