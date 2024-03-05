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
    class FVerifyItemSetByUserIdRequest;

    class GS2INVENTORY_API FVerifyItemSetByUserIdRequest final : public TSharedFromThis<FVerifyItemSetByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<int64> CountValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyItemSetByUserIdRequest();
        FVerifyItemSetByUserIdRequest(
            const FVerifyItemSetByUserIdRequest& From
        );
        ~FVerifyItemSetByUserIdRequest() = default;

        TSharedPtr<FVerifyItemSetByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithCount(const TOptional<int64> Count);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyItemSetByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyItemSetByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyItemSetByUserIdRequest, ESPMode::ThreadSafe> FVerifyItemSetByUserIdRequestPtr;
}