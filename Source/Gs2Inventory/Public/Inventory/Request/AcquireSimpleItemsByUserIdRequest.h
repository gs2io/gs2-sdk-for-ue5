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
#include "../Model/AcquireCount.h"

namespace Gs2::Inventory::Request
{
    class FAcquireSimpleItemsByUserIdRequest;

    class GS2INVENTORY_API FAcquireSimpleItemsByUserIdRequest final : public TSharedFromThis<FAcquireSimpleItemsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireCount>>> AcquireCountsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquireSimpleItemsByUserIdRequest();
        FAcquireSimpleItemsByUserIdRequest(
            const FAcquireSimpleItemsByUserIdRequest& From
        );
        ~FAcquireSimpleItemsByUserIdRequest() = default;

        TSharedPtr<FAcquireSimpleItemsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireSimpleItemsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquireSimpleItemsByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FAcquireSimpleItemsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcquireSimpleItemsByUserIdRequest> WithAcquireCounts(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireCount>>> AcquireCounts);
        TSharedPtr<FAcquireSimpleItemsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAcquireSimpleItemsByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireCount>>> GetAcquireCounts() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquireSimpleItemsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireSimpleItemsByUserIdRequest> FAcquireSimpleItemsByUserIdRequestPtr;
}