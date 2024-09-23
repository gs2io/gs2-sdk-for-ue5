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

namespace Gs2::Showcase::Request
{
    class FIncrementPurchaseCountRequest;

    class GS2SHOWCASE_API FIncrementPurchaseCountRequest final : public TSharedFromThis<FIncrementPurchaseCountRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FIncrementPurchaseCountRequest();
        FIncrementPurchaseCountRequest(
            const FIncrementPurchaseCountRequest& From
        );
        ~FIncrementPurchaseCountRequest() = default;

        TSharedPtr<FIncrementPurchaseCountRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIncrementPurchaseCountRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIncrementPurchaseCountRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FIncrementPurchaseCountRequest> WithDisplayItemName(const TOptional<FString> DisplayItemName);
        TSharedPtr<FIncrementPurchaseCountRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FIncrementPurchaseCountRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FIncrementPurchaseCountRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FIncrementPurchaseCountRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncrementPurchaseCountRequest, ESPMode::ThreadSafe> FIncrementPurchaseCountRequestPtr;
}