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
    class FEmitRequest;

    class GS2STATEMACHINE_API FEmitRequest final : public TSharedFromThis<FEmitRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> StatusNameValue;
        TOptional<FString> EventNameValue;
        TOptional<FString> ArgsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FEmitRequest();
        FEmitRequest(
            const FEmitRequest& From
        );
        ~FEmitRequest() = default;

        TSharedPtr<FEmitRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FEmitRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FEmitRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FEmitRequest> WithStatusName(const TOptional<FString> StatusName);
        TSharedPtr<FEmitRequest> WithEventName(const TOptional<FString> EventName);
        TSharedPtr<FEmitRequest> WithArgs(const TOptional<FString> Args);
        TSharedPtr<FEmitRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetStatusName() const;
        TOptional<FString> GetEventName() const;
        TOptional<FString> GetArgs() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FEmitRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEmitRequest> FEmitRequestPtr;
}