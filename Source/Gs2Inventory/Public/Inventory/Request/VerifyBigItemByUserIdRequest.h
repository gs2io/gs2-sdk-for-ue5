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
    class FVerifyBigItemByUserIdRequest;

    class GS2INVENTORY_API FVerifyBigItemByUserIdRequest final : public TSharedFromThis<FVerifyBigItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> CountValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyBigItemByUserIdRequest();
        FVerifyBigItemByUserIdRequest(
            const FVerifyBigItemByUserIdRequest& From
        );
        ~FVerifyBigItemByUserIdRequest() = default;

        TSharedPtr<FVerifyBigItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithCount(const TOptional<FString> Count);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyBigItemByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetCount() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyBigItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyBigItemByUserIdRequest, ESPMode::ThreadSafe> FVerifyBigItemByUserIdRequestPtr;
}