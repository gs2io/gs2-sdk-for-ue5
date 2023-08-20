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
    class FDeleteBigItemByUserIdRequest;

    class GS2INVENTORY_API FDeleteBigItemByUserIdRequest final : public TSharedFromThis<FDeleteBigItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteBigItemByUserIdRequest();
        FDeleteBigItemByUserIdRequest(
            const FDeleteBigItemByUserIdRequest& From
        );
        ~FDeleteBigItemByUserIdRequest() = default;

        TSharedPtr<FDeleteBigItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteBigItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteBigItemByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FDeleteBigItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteBigItemByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FDeleteBigItemByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteBigItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteBigItemByUserIdRequest, ESPMode::ThreadSafe> FDeleteBigItemByUserIdRequestPtr;
}