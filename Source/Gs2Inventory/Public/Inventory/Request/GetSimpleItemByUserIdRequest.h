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
    class FGetSimpleItemByUserIdRequest;

    class GS2INVENTORY_API FGetSimpleItemByUserIdRequest final : public TSharedFromThis<FGetSimpleItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetSimpleItemByUserIdRequest();
        FGetSimpleItemByUserIdRequest(
            const FGetSimpleItemByUserIdRequest& From
        );
        ~FGetSimpleItemByUserIdRequest() = default;

        TSharedPtr<FGetSimpleItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSimpleItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSimpleItemByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetSimpleItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetSimpleItemByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FGetSimpleItemByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetSimpleItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSimpleItemByUserIdRequest> FGetSimpleItemByUserIdRequestPtr;
}