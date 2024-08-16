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

namespace Gs2::Ranking::Request
{
    class FUnsubscribeRequest;

    class GS2RANKING_API FUnsubscribeRequest final : public TSharedFromThis<FUnsubscribeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUnsubscribeRequest();
        FUnsubscribeRequest(
            const FUnsubscribeRequest& From
        );
        ~FUnsubscribeRequest() = default;

        TSharedPtr<FUnsubscribeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUnsubscribeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUnsubscribeRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FUnsubscribeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUnsubscribeRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FUnsubscribeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUnsubscribeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnsubscribeRequest> FUnsubscribeRequestPtr;
}