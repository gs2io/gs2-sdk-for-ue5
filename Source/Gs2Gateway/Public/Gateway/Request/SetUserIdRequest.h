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
    class FSetUserIdRequest;

    class GS2GATEWAY_API FSetUserIdRequest final : public TSharedFromThis<FSetUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<bool> AllowConcurrentAccessValue;
        TOptional<bool> ForceValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetUserIdRequest();
        FSetUserIdRequest(
            const FSetUserIdRequest& From
        );
        ~FSetUserIdRequest() = default;

        TSharedPtr<FSetUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetUserIdRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetUserIdRequest> WithAllowConcurrentAccess(const TOptional<bool> AllowConcurrentAccess);
        TSharedPtr<FSetUserIdRequest> WithForce(const TOptional<bool> Force);
        TSharedPtr<FSetUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<bool> GetAllowConcurrentAccess() const;
        FString GetAllowConcurrentAccessString() const;
        TOptional<bool> GetForce() const;
        FString GetForceString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetUserIdRequest> FSetUserIdRequestPtr;
}