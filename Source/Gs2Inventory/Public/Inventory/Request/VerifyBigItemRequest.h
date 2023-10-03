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
    class FVerifyBigItemRequest;

    class GS2INVENTORY_API FVerifyBigItemRequest final : public TSharedFromThis<FVerifyBigItemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyBigItemRequest();
        FVerifyBigItemRequest(
            const FVerifyBigItemRequest& From
        );
        ~FVerifyBigItemRequest() = default;

        TSharedPtr<FVerifyBigItemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyBigItemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyBigItemRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyBigItemRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyBigItemRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifyBigItemRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyBigItemRequest> WithCount(const TOptional<FString> Count);
        TSharedPtr<FVerifyBigItemRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetCount() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyBigItemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyBigItemRequest, ESPMode::ThreadSafe> FVerifyBigItemRequestPtr;
}