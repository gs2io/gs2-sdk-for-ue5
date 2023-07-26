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

namespace Gs2::StateMachine::Request
{
    class FExitStateMachineByUserIdRequest;

    class GS2STATEMACHINE_API FExitStateMachineByUserIdRequest final : public TSharedFromThis<FExitStateMachineByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> StatusNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FExitStateMachineByUserIdRequest();
        FExitStateMachineByUserIdRequest(
            const FExitStateMachineByUserIdRequest& From
        );
        ~FExitStateMachineByUserIdRequest() = default;

        TSharedPtr<FExitStateMachineByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FExitStateMachineByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FExitStateMachineByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FExitStateMachineByUserIdRequest> WithStatusName(const TOptional<FString> StatusName);
        TSharedPtr<FExitStateMachineByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetStatusName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FExitStateMachineByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FExitStateMachineByUserIdRequest, ESPMode::ThreadSafe> FExitStateMachineByUserIdRequestPtr;
}