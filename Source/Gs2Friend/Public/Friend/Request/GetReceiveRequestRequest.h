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

namespace Gs2::Friend::Request
{
    class FGetReceiveRequestRequest;

    class GS2FRIEND_API FGetReceiveRequestRequest final : public TSharedFromThis<FGetReceiveRequestRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> FromUserIdValue;
        
    public:
        
        FGetReceiveRequestRequest();
        FGetReceiveRequestRequest(
            const FGetReceiveRequestRequest& From
        );
        ~FGetReceiveRequestRequest() = default;

        TSharedPtr<FGetReceiveRequestRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetReceiveRequestRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetReceiveRequestRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetReceiveRequestRequest> WithFromUserId(const TOptional<FString> FromUserId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetFromUserId() const;

        static TSharedPtr<FGetReceiveRequestRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetReceiveRequestRequest, ESPMode::ThreadSafe> FGetReceiveRequestRequestPtr;
}