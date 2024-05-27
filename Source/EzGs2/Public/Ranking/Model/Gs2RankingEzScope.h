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
#include "Ranking/Model/Scope.h"

namespace Gs2::UE5::Ranking::Model
{
	class EZGS2_API FEzScope final : public TSharedFromThis<FEzScope>
	{
        TOptional<FString> NameValue;
        TOptional<int64> TargetDaysValue;

	public:
        TSharedPtr<FEzScope> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzScope> WithTargetDays(const TOptional<int64> TargetDays);

        TOptional<FString> GetName() const;

        TOptional<int64> GetTargetDays() const;
        FString GetTargetDaysString() const;

        Gs2::Ranking::Model::FScopePtr ToModel() const;
        static TSharedPtr<FEzScope> FromModel(Gs2::Ranking::Model::FScopePtr Model);
    };
    typedef TSharedPtr<FEzScope> FEzScopePtr;
}