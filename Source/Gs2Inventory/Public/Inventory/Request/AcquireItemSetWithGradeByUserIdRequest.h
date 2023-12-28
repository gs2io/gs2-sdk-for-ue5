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
    class FAcquireItemSetWithGradeByUserIdRequest;

    class GS2INVENTORY_API FAcquireItemSetWithGradeByUserIdRequest final : public TSharedFromThis<FAcquireItemSetWithGradeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GradeModelIdValue;
        TOptional<int64> GradeValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquireItemSetWithGradeByUserIdRequest();
        FAcquireItemSetWithGradeByUserIdRequest(
            const FAcquireItemSetWithGradeByUserIdRequest& From
        );
        ~FAcquireItemSetWithGradeByUserIdRequest() = default;

        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithGradeModelId(const TOptional<FString> GradeModelId);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGradeModelId() const;
        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireItemSetWithGradeByUserIdRequest, ESPMode::ThreadSafe> FAcquireItemSetWithGradeByUserIdRequestPtr;
}