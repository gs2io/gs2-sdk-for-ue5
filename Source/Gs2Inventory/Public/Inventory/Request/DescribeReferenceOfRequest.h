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

namespace Gs2::Inventory::Request
{
    class FDescribeReferenceOfRequest;

    class GS2INVENTORY_API FDescribeReferenceOfRequest final : public TSharedFromThis<FDescribeReferenceOfRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        
    public:
        
        FDescribeReferenceOfRequest();
        FDescribeReferenceOfRequest(
            const FDescribeReferenceOfRequest& From
        );
        ~FDescribeReferenceOfRequest() = default;

        TSharedPtr<FDescribeReferenceOfRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeReferenceOfRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeReferenceOfRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FDescribeReferenceOfRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeReferenceOfRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FDescribeReferenceOfRequest> WithItemSetName(const TOptional<FString> ItemSetName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;

        static TSharedPtr<FDescribeReferenceOfRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeReferenceOfRequest, ESPMode::ThreadSafe> FDescribeReferenceOfRequestPtr;
}