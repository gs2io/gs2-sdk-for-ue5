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
    class FOpenMessageRequest;

    class GS2INBOX_API FOpenMessageRequest final : public TSharedFromThis<FOpenMessageRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MessageNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FOpenMessageRequest();
        FOpenMessageRequest(
            const FOpenMessageRequest& From
        );
        ~FOpenMessageRequest() = default;

        TSharedPtr<FOpenMessageRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FOpenMessageRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FOpenMessageRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FOpenMessageRequest> WithMessageName(const TOptional<FString> MessageName);
        TSharedPtr<FOpenMessageRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMessageName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FOpenMessageRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FOpenMessageRequest, ESPMode::ThreadSafe> FOpenMessageRequestPtr;
}