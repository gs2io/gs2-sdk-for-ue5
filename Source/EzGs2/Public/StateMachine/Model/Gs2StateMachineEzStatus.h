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
#include "StateMachine/Model/Status.h"
#include "Gs2StateMachineEzRandomStatus.h"
#include "Gs2StateMachineEzStackEntry.h"
#include "Gs2StateMachineEzVariable.h"

namespace Gs2::UE5::StateMachine::Model
{
	class EZGS2_API FEzStatus final : public TSharedFromThis<FEzStatus>
	{
        TOptional<FString> StatusIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> EnableSpeculativeExecutionValue;
        TOptional<FString> StateMachineDefinitionValue;
        TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomStatus> RandomStatusValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzStackEntry>>> StacksValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVariable>>> VariablesValue;
        TOptional<FString> StatusValue;
        TOptional<FString> LastErrorValue;
        TOptional<int32> TransitionCountValue;

	public:
        TSharedPtr<FEzStatus> WithStatusId(const TOptional<FString> StatusId);
        TSharedPtr<FEzStatus> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzStatus> WithEnableSpeculativeExecution(const TOptional<FString> EnableSpeculativeExecution);
        TSharedPtr<FEzStatus> WithStateMachineDefinition(const TOptional<FString> StateMachineDefinition);
        TSharedPtr<FEzStatus> WithRandomStatus(const TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomStatus> RandomStatus);
        TSharedPtr<FEzStatus> WithStacks(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzStackEntry>>> Stacks);
        TSharedPtr<FEzStatus> WithVariables(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVariable>>> Variables);
        TSharedPtr<FEzStatus> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FEzStatus> WithLastError(const TOptional<FString> LastError);
        TSharedPtr<FEzStatus> WithTransitionCount(const TOptional<int32> TransitionCount);

        TOptional<FString> GetStatusId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetEnableSpeculativeExecution() const;

        TOptional<FString> GetStateMachineDefinition() const;

        TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomStatus> GetRandomStatus() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzStackEntry>>> GetStacks() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVariable>>> GetVariables() const;

        TOptional<FString> GetStatus() const;

        TOptional<FString> GetLastError() const;

        TOptional<int32> GetTransitionCount() const;
        FString GetTransitionCountString() const;

        Gs2::StateMachine::Model::FStatusPtr ToModel() const;
        static TSharedPtr<FEzStatus> FromModel(Gs2::StateMachine::Model::FStatusPtr Model);
    };
    typedef TSharedPtr<FEzStatus> FEzStatusPtr;
}