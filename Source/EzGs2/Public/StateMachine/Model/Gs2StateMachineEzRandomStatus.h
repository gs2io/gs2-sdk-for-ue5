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
#include "StateMachine/Model/RandomStatus.h"
#include "Gs2StateMachineEzRandomUsed.h"

namespace Gs2::UE5::StateMachine::Model
{
	class EZGS2_API FEzRandomStatus final : public TSharedFromThis<FEzRandomStatus>
	{
        TOptional<int64> SeedValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomUsed>>> UsedValue;

	public:
        TSharedPtr<FEzRandomStatus> WithSeed(const TOptional<int64> Seed);
        TSharedPtr<FEzRandomStatus> WithUsed(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomUsed>>> Used);

        TOptional<int64> GetSeed() const;
        FString GetSeedString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomUsed>>> GetUsed() const;

        Gs2::StateMachine::Model::FRandomStatusPtr ToModel() const;
        static TSharedPtr<FEzRandomStatus> FromModel(Gs2::StateMachine::Model::FRandomStatusPtr Model);
    };
    typedef TSharedPtr<FEzRandomStatus> FEzRandomStatusPtr;
}