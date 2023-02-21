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
    class FDeleteItemSetByUserIdRequest;

    class GS2INVENTORY_API FDeleteItemSetByUserIdRequest final : public TSharedFromThis<FDeleteItemSetByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteItemSetByUserIdRequest();
        FDeleteItemSetByUserIdRequest(
            const FDeleteItemSetByUserIdRequest& From
        );
        ~FDeleteItemSetByUserIdRequest() = default;

        TSharedPtr<FDeleteItemSetByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteItemSetByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteItemSetByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FDeleteItemSetByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteItemSetByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FDeleteItemSetByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FDeleteItemSetByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteItemSetByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteItemSetByUserIdRequest, ESPMode::ThreadSafe> FDeleteItemSetByUserIdRequestPtr;
}