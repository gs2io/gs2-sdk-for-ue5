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
#include "../Model/Config.h"

namespace Gs2::Inbox::Request
{
    class FReadMessageRequest;

    class GS2INBOX_API FReadMessageRequest final : public TSharedFromThis<FReadMessageRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MessageNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReadMessageRequest();
        FReadMessageRequest(
            const FReadMessageRequest& From
        );
        ~FReadMessageRequest() = default;

        TSharedPtr<FReadMessageRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReadMessageRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReadMessageRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FReadMessageRequest> WithMessageName(const TOptional<FString> MessageName);
        TSharedPtr<FReadMessageRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReadMessageRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMessageName() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReadMessageRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReadMessageRequest, ESPMode::ThreadSafe> FReadMessageRequestPtr;
}