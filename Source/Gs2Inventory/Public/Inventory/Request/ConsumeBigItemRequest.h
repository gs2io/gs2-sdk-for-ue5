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
    class FConsumeBigItemRequest;

    class GS2INVENTORY_API FConsumeBigItemRequest final : public TSharedFromThis<FConsumeBigItemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ConsumeCountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeBigItemRequest();
        FConsumeBigItemRequest(
            const FConsumeBigItemRequest& From
        );
        ~FConsumeBigItemRequest() = default;

        TSharedPtr<FConsumeBigItemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeBigItemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeBigItemRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FConsumeBigItemRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FConsumeBigItemRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FConsumeBigItemRequest> WithConsumeCount(const TOptional<FString> ConsumeCount);
        TSharedPtr<FConsumeBigItemRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetConsumeCount() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeBigItemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeBigItemRequest, ESPMode::ThreadSafe> FConsumeBigItemRequestPtr;
}