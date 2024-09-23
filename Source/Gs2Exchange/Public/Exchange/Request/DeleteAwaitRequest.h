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

namespace Gs2::Exchange::Request
{
    class FDeleteAwaitRequest;

    class GS2EXCHANGE_API FDeleteAwaitRequest final : public TSharedFromThis<FDeleteAwaitRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> AwaitNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteAwaitRequest();
        FDeleteAwaitRequest(
            const FDeleteAwaitRequest& From
        );
        ~FDeleteAwaitRequest() = default;

        TSharedPtr<FDeleteAwaitRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteAwaitRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteAwaitRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteAwaitRequest> WithAwaitName(const TOptional<FString> AwaitName);
        TSharedPtr<FDeleteAwaitRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetAwaitName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteAwaitRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteAwaitRequest, ESPMode::ThreadSafe> FDeleteAwaitRequestPtr;
}