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
#include "StateMachine/Model/StackEntry.h"

namespace Gs2::UE5::StateMachine::Model
{
	class EZGS2_API FEzStackEntry final : public TSharedFromThis<FEzStackEntry>
	{
        TOptional<FString> StateMachineNameValue;
        TOptional<FString> TaskNameValue;

	public:
        TSharedPtr<FEzStackEntry> WithStateMachineName(const TOptional<FString> StateMachineName);
        TSharedPtr<FEzStackEntry> WithTaskName(const TOptional<FString> TaskName);

        TOptional<FString> GetStateMachineName() const;

        TOptional<FString> GetTaskName() const;

        Gs2::StateMachine::Model::FStackEntryPtr ToModel() const;
        static TSharedPtr<FEzStackEntry> FromModel(Gs2::StateMachine::Model::FStackEntryPtr Model);
    };
    typedef TSharedPtr<FEzStackEntry> FEzStackEntryPtr;
}