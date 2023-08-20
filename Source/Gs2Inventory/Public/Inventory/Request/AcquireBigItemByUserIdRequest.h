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
    class FAcquireBigItemByUserIdRequest;

    class GS2INVENTORY_API FAcquireBigItemByUserIdRequest final : public TSharedFromThis<FAcquireBigItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> AcquireCountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquireBigItemByUserIdRequest();
        FAcquireBigItemByUserIdRequest(
            const FAcquireBigItemByUserIdRequest& From
        );
        ~FAcquireBigItemByUserIdRequest() = default;

        TSharedPtr<FAcquireBigItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireBigItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquireBigItemByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FAcquireBigItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcquireBigItemByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FAcquireBigItemByUserIdRequest> WithAcquireCount(const TOptional<FString> AcquireCount);
        TSharedPtr<FAcquireBigItemByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetAcquireCount() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquireBigItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireBigItemByUserIdRequest, ESPMode::ThreadSafe> FAcquireBigItemByUserIdRequestPtr;
}