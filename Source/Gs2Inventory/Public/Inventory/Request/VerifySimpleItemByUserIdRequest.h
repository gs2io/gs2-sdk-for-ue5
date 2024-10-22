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
    class FVerifySimpleItemByUserIdRequest;

    class GS2INVENTORY_API FVerifySimpleItemByUserIdRequest final : public TSharedFromThis<FVerifySimpleItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> CountValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifySimpleItemByUserIdRequest();
        FVerifySimpleItemByUserIdRequest(
            const FVerifySimpleItemByUserIdRequest& From
        );
        ~FVerifySimpleItemByUserIdRequest() = default;

        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithCount(const TOptional<int64> Count);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifySimpleItemByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifySimpleItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifySimpleItemByUserIdRequest> FVerifySimpleItemByUserIdRequestPtr;
}