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
    class FSetBigItemByUserIdRequest;

    class GS2INVENTORY_API FSetBigItemByUserIdRequest final : public TSharedFromThis<FSetBigItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetBigItemByUserIdRequest();
        FSetBigItemByUserIdRequest(
            const FSetBigItemByUserIdRequest& From
        );
        ~FSetBigItemByUserIdRequest() = default;

        TSharedPtr<FSetBigItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetBigItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetBigItemByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FSetBigItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetBigItemByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FSetBigItemByUserIdRequest> WithCount(const TOptional<FString> Count);
        TSharedPtr<FSetBigItemByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetCount() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetBigItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetBigItemByUserIdRequest, ESPMode::ThreadSafe> FSetBigItemByUserIdRequestPtr;
}