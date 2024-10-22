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

namespace Gs2::Inventory::Request
{
    class FGetSimpleItemRequest;

    class GS2INVENTORY_API FGetSimpleItemRequest final : public TSharedFromThis<FGetSimpleItemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        
    public:
        
        FGetSimpleItemRequest();
        FGetSimpleItemRequest(
            const FGetSimpleItemRequest& From
        );
        ~FGetSimpleItemRequest() = default;

        TSharedPtr<FGetSimpleItemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSimpleItemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSimpleItemRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetSimpleItemRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetSimpleItemRequest> WithItemName(const TOptional<FString> ItemName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;

        static TSharedPtr<FGetSimpleItemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSimpleItemRequest> FGetSimpleItemRequestPtr;
}