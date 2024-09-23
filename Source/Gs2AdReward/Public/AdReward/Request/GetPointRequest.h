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

namespace Gs2::AdReward::Request
{
    class FGetPointRequest;

    class GS2ADREWARD_API FGetPointRequest final : public TSharedFromThis<FGetPointRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetPointRequest();
        FGetPointRequest(
            const FGetPointRequest& From
        );
        ~FGetPointRequest() = default;

        TSharedPtr<FGetPointRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetPointRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetPointRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetPointRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPointRequest, ESPMode::ThreadSafe> FGetPointRequestPtr;
}