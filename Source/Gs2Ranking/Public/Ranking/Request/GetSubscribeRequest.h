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

namespace Gs2::Ranking::Request
{
    class FGetSubscribeRequest;

    class GS2RANKING_API FGetSubscribeRequest final : public TSharedFromThis<FGetSubscribeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        
    public:
        
        FGetSubscribeRequest();
        FGetSubscribeRequest(
            const FGetSubscribeRequest& From
        );
        ~FGetSubscribeRequest() = default;

        TSharedPtr<FGetSubscribeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSubscribeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSubscribeRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FGetSubscribeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetSubscribeRequest> WithTargetUserId(const TOptional<FString> TargetUserId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;

        static TSharedPtr<FGetSubscribeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSubscribeRequest, ESPMode::ThreadSafe> FGetSubscribeRequestPtr;
}