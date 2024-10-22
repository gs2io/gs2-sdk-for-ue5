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

namespace Gs2::Gateway::Request
{
    class FSetFirebaseTokenRequest;

    class GS2GATEWAY_API FSetFirebaseTokenRequest final : public TSharedFromThis<FSetFirebaseTokenRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetFirebaseTokenRequest();
        FSetFirebaseTokenRequest(
            const FSetFirebaseTokenRequest& From
        );
        ~FSetFirebaseTokenRequest() = default;

        TSharedPtr<FSetFirebaseTokenRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetFirebaseTokenRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetFirebaseTokenRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetFirebaseTokenRequest> WithToken(const TOptional<FString> Token);
        TSharedPtr<FSetFirebaseTokenRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetFirebaseTokenRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetFirebaseTokenRequest> FSetFirebaseTokenRequestPtr;
}