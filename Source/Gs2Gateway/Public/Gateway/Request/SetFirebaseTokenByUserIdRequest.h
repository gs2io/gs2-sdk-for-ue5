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

namespace Gs2::Gateway::Request
{
    class FSetFirebaseTokenByUserIdRequest;

    class GS2GATEWAY_API FSetFirebaseTokenByUserIdRequest final : public TSharedFromThis<FSetFirebaseTokenByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetFirebaseTokenByUserIdRequest();
        FSetFirebaseTokenByUserIdRequest(
            const FSetFirebaseTokenByUserIdRequest& From
        );
        ~FSetFirebaseTokenByUserIdRequest() = default;

        TSharedPtr<FSetFirebaseTokenByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetFirebaseTokenByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetFirebaseTokenByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetFirebaseTokenByUserIdRequest> WithToken(const TOptional<FString> Token);
        TSharedPtr<FSetFirebaseTokenByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetFirebaseTokenByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetFirebaseTokenByUserIdRequest, ESPMode::ThreadSafe> FSetFirebaseTokenByUserIdRequestPtr;
}