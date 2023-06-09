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
#include "Idle/Model/Status.h"

namespace Gs2::UE5::Idle::Model
{
	class EZGS2_API FEzStatus final : public TSharedFromThis<FEzStatus>
	{
        TOptional<FString> CategoryNameValue;
        TOptional<int64> RandomSeedValue;
        TOptional<int32> IdleMinutesValue;

	public:
        TSharedPtr<FEzStatus> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FEzStatus> WithRandomSeed(const TOptional<int64> RandomSeed);
        TSharedPtr<FEzStatus> WithIdleMinutes(const TOptional<int32> IdleMinutes);

        TOptional<FString> GetCategoryName() const;

        TOptional<int64> GetRandomSeed() const;
        FString GetRandomSeedString() const;

        TOptional<int32> GetIdleMinutes() const;
        FString GetIdleMinutesString() const;

        Gs2::Idle::Model::FStatusPtr ToModel() const;
        static TSharedPtr<FEzStatus> FromModel(Gs2::Idle::Model::FStatusPtr Model);
    };
    typedef TSharedPtr<FEzStatus> FEzStatusPtr;
}