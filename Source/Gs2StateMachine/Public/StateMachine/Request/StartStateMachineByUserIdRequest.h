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
    class FStartStateMachineByUserIdRequest;

    class GS2STATEMACHINE_API FStartStateMachineByUserIdRequest final : public TSharedFromThis<FStartStateMachineByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ArgsValue;
        TOptional<int32> TtlValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FStartStateMachineByUserIdRequest();
        FStartStateMachineByUserIdRequest(
            const FStartStateMachineByUserIdRequest& From
        );
        ~FStartStateMachineByUserIdRequest() = default;

        TSharedPtr<FStartStateMachineByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FStartStateMachineByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FStartStateMachineByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStartStateMachineByUserIdRequest> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FStartStateMachineByUserIdRequest> WithTtl(const TOptional<int32> Ttl);
        TSharedPtr<FStartStateMachineByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FStartStateMachineByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetArgs() const;
        TOptional<int32> GetTtl() const;
        FString GetTtlString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FStartStateMachineByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FStartStateMachineByUserIdRequest, ESPMode::ThreadSafe> FStartStateMachineByUserIdRequestPtr;
}