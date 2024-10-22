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
    class FAcquireItemSetByUserIdRequest;

    class GS2INVENTORY_API FAcquireItemSetByUserIdRequest final : public TSharedFromThis<FAcquireItemSetByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> AcquireCountValue;
        TOptional<int64> ExpiresAtValue;
        TOptional<bool> CreateNewItemSetValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquireItemSetByUserIdRequest();
        FAcquireItemSetByUserIdRequest(
            const FAcquireItemSetByUserIdRequest& From
        );
        ~FAcquireItemSetByUserIdRequest() = default;

        TSharedPtr<FAcquireItemSetByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithAcquireCount(const TOptional<int64> AcquireCount);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithCreateNewItemSet(const TOptional<bool> CreateNewItemSet);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAcquireItemSetByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetAcquireCount() const;
        FString GetAcquireCountString() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TOptional<bool> GetCreateNewItemSet() const;
        FString GetCreateNewItemSetString() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquireItemSetByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequestPtr;
}