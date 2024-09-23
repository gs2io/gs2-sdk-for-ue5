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

namespace Gs2::Chat::Request
{
    class FGetMessageRequest;

    class GS2CHAT_API FGetMessageRequest final : public TSharedFromThis<FGetMessageRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> MessageNameValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetMessageRequest();
        FGetMessageRequest(
            const FGetMessageRequest& From
        );
        ~FGetMessageRequest() = default;

        TSharedPtr<FGetMessageRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMessageRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMessageRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FGetMessageRequest> WithMessageName(const TOptional<FString> MessageName);
        TSharedPtr<FGetMessageRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FGetMessageRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetMessageName() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetMessageRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMessageRequest, ESPMode::ThreadSafe> FGetMessageRequestPtr;
}