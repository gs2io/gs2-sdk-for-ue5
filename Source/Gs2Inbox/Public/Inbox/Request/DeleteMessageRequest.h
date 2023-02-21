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

namespace Gs2::Inbox::Request
{
    class FDeleteMessageRequest;

    class GS2INBOX_API FDeleteMessageRequest final : public TSharedFromThis<FDeleteMessageRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MessageNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteMessageRequest();
        FDeleteMessageRequest(
            const FDeleteMessageRequest& From
        );
        ~FDeleteMessageRequest() = default;

        TSharedPtr<FDeleteMessageRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteMessageRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteMessageRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteMessageRequest> WithMessageName(const TOptional<FString> MessageName);
        TSharedPtr<FDeleteMessageRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMessageName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteMessageRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMessageRequest, ESPMode::ThreadSafe> FDeleteMessageRequestPtr;
}