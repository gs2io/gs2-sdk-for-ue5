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
#include "Core/Gs2Object.h"
#include "RandomStatus.h"
#include "StackEntry.h"
#include "Variable.h"

namespace Gs2::StateMachine::Model
{
    class GS2STATEMACHINE_API FStatus final : public FGs2Object, public TSharedFromThis<FStatus>
    {
        TOptional<FString> StatusIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TOptional<int64> StateMachineVersionValue;
        TOptional<FString> EnableSpeculativeExecutionValue;
        TOptional<FString> StateMachineDefinitionValue;
        TSharedPtr<FRandomStatus> RandomStatusValue;
        TSharedPtr<TArray<TSharedPtr<FStackEntry>>> StacksValue;
        TSharedPtr<TArray<TSharedPtr<FVariable>>> VariablesValue;
        TOptional<FString> StatusValue;
        TOptional<FString> LastErrorValue;
        TOptional<int32> TransitionCountValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FStatus();
        FStatus(
            const FStatus& From
        );
        virtual ~FStatus() override = default;

        TSharedPtr<FStatus> WithStatusId(const TOptional<FString> StatusId);
        TSharedPtr<FStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStatus> WithName(const TOptional<FString> Name);
        TSharedPtr<FStatus> WithStateMachineVersion(const TOptional<int64> StateMachineVersion);
        TSharedPtr<FStatus> WithEnableSpeculativeExecution(const TOptional<FString> EnableSpeculativeExecution);
        TSharedPtr<FStatus> WithStateMachineDefinition(const TOptional<FString> StateMachineDefinition);
        TSharedPtr<FStatus> WithRandomStatus(const TSharedPtr<FRandomStatus> RandomStatus);
        TSharedPtr<FStatus> WithStacks(const TSharedPtr<TArray<TSharedPtr<FStackEntry>>> Stacks);
        TSharedPtr<FStatus> WithVariables(const TSharedPtr<TArray<TSharedPtr<FVariable>>> Variables);
        TSharedPtr<FStatus> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FStatus> WithLastError(const TOptional<FString> LastError);
        TSharedPtr<FStatus> WithTransitionCount(const TOptional<int32> TransitionCount);
        TSharedPtr<FStatus> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStatus> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetStatusId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;
        TOptional<int64> GetStateMachineVersion() const;
        FString GetStateMachineVersionString() const;
        TOptional<FString> GetEnableSpeculativeExecution() const;
        TOptional<FString> GetStateMachineDefinition() const;
        TSharedPtr<FRandomStatus> GetRandomStatus() const;
        TSharedPtr<TArray<TSharedPtr<FStackEntry>>> GetStacks() const;
        TSharedPtr<TArray<TSharedPtr<FVariable>>> GetVariables() const;
        TOptional<FString> GetStatus() const;
        TOptional<FString> GetLastError() const;
        TOptional<int32> GetTransitionCount() const;
        FString GetTransitionCountString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetStatusNameFromGrn(const FString Grn);

        static TSharedPtr<FStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStatus, ESPMode::ThreadSafe> FStatusPtr;
}