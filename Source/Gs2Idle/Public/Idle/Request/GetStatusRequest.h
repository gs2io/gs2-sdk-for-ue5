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

namespace Gs2::Idle::Request
{
    class FGetStatusRequest;

    class GS2IDLE_API FGetStatusRequest final : public TSharedFromThis<FGetStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> CategoryNameValue;
        
    public:
        
        FGetStatusRequest();
        FGetStatusRequest(
            const FGetStatusRequest& From
        );
        ~FGetStatusRequest() = default;

        TSharedPtr<FGetStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetStatusRequest> WithCategoryName(const TOptional<FString> CategoryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetCategoryName() const;

        static TSharedPtr<FGetStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStatusRequest> FGetStatusRequestPtr;
}