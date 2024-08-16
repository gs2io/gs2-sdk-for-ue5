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
    class FGetItemSetRequest;

    class GS2INVENTORY_API FGetItemSetRequest final : public TSharedFromThis<FGetItemSetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        
    public:
        
        FGetItemSetRequest();
        FGetItemSetRequest(
            const FGetItemSetRequest& From
        );
        ~FGetItemSetRequest() = default;

        TSharedPtr<FGetItemSetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetItemSetRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetItemSetRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetItemSetRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetItemSetRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FGetItemSetRequest> WithItemSetName(const TOptional<FString> ItemSetName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;

        static TSharedPtr<FGetItemSetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetItemSetRequest> FGetItemSetRequestPtr;
}