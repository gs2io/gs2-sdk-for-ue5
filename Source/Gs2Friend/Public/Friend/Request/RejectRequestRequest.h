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
    class FRejectRequestRequest;

    class GS2FRIEND_API FRejectRequestRequest final : public TSharedFromThis<FRejectRequestRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> FromUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRejectRequestRequest();
        FRejectRequestRequest(
            const FRejectRequestRequest& From
        );
        ~FRejectRequestRequest() = default;

        TSharedPtr<FRejectRequestRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRejectRequestRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRejectRequestRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FRejectRequestRequest> WithFromUserId(const TOptional<FString> FromUserId);
        TSharedPtr<FRejectRequestRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetFromUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRejectRequestRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRejectRequestRequest, ESPMode::ThreadSafe> FRejectRequestRequestPtr;
}