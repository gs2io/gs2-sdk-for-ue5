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
    class FVerifySimpleItemRequest;

    class GS2INVENTORY_API FVerifySimpleItemRequest final : public TSharedFromThis<FVerifySimpleItemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifySimpleItemRequest();
        FVerifySimpleItemRequest(
            const FVerifySimpleItemRequest& From
        );
        ~FVerifySimpleItemRequest() = default;

        TSharedPtr<FVerifySimpleItemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifySimpleItemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifySimpleItemRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifySimpleItemRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifySimpleItemRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifySimpleItemRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifySimpleItemRequest> WithCount(const TOptional<int64> Count);
        TSharedPtr<FVerifySimpleItemRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifySimpleItemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifySimpleItemRequest, ESPMode::ThreadSafe> FVerifySimpleItemRequestPtr;
}