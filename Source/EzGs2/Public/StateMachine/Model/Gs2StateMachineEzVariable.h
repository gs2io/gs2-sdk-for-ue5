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
#include "StateMachine/Model/Variable.h"

namespace Gs2::UE5::StateMachine::Model
{
	class EZGS2_API FEzVariable final : public TSharedFromThis<FEzVariable>
	{
        TOptional<FString> StateMachineNameValue;
        TOptional<FString> ValueValue;

	public:
        TSharedPtr<FEzVariable> WithStateMachineName(const TOptional<FString> StateMachineName);
        TSharedPtr<FEzVariable> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetStateMachineName() const;

        TOptional<FString> GetValue() const;

        Gs2::StateMachine::Model::FVariablePtr ToModel() const;
        static TSharedPtr<FEzVariable> FromModel(Gs2::StateMachine::Model::FVariablePtr Model);
    };
    typedef TSharedPtr<FEzVariable> FEzVariablePtr;
}