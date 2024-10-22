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
#include "Dom/JsonObject.h"

namespace Gs2::StateMachine::Request
{
    class FEmitByUserIdRequest;

    class GS2STATEMACHINE_API FEmitByUserIdRequest final : public TSharedFromThis<FEmitByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> StatusNameValue;
        TOptional<FString> EventNameValue;
        TOptional<FString> ArgsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FEmitByUserIdRequest();
        FEmitByUserIdRequest(
            const FEmitByUserIdRequest& From
        );
        ~FEmitByUserIdRequest() = default;

        TSharedPtr<FEmitByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FEmitByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FEmitByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEmitByUserIdRequest> WithStatusName(const TOptional<FString> StatusName);
        TSharedPtr<FEmitByUserIdRequest> WithEventName(const TOptional<FString> EventName);
        TSharedPtr<FEmitByUserIdRequest> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FEmitByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FEmitByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetStatusName() const;
        TOptional<FString> GetEventName() const;
        TOptional<FString> GetArgs() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FEmitByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEmitByUserIdRequest> FEmitByUserIdRequestPtr;
}