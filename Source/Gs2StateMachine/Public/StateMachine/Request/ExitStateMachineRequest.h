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
    class FExitStateMachineRequest;

    class GS2STATEMACHINE_API FExitStateMachineRequest final : public TSharedFromThis<FExitStateMachineRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> StatusNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FExitStateMachineRequest();
        FExitStateMachineRequest(
            const FExitStateMachineRequest& From
        );
        ~FExitStateMachineRequest() = default;

        TSharedPtr<FExitStateMachineRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FExitStateMachineRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FExitStateMachineRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FExitStateMachineRequest> WithStatusName(const TOptional<FString> StatusName);
        TSharedPtr<FExitStateMachineRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetStatusName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FExitStateMachineRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FExitStateMachineRequest, ESPMode::ThreadSafe> FExitStateMachineRequestPtr;
}