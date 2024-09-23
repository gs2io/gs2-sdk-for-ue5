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

namespace Gs2::SerialKey::Request
{
    class FUseRequest;

    class GS2SERIALKEY_API FUseRequest final : public TSharedFromThis<FUseRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> CodeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUseRequest();
        FUseRequest(
            const FUseRequest& From
        );
        ~FUseRequest() = default;

        TSharedPtr<FUseRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUseRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUseRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUseRequest> WithCode(const TOptional<FString> Code);
        TSharedPtr<FUseRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetCode() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUseRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUseRequest, ESPMode::ThreadSafe> FUseRequestPtr;
}