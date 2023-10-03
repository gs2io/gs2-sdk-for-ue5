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
    class FVerifyItemSetRequest;

    class GS2INVENTORY_API FVerifyItemSetRequest final : public TSharedFromThis<FVerifyItemSetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<int64> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyItemSetRequest();
        FVerifyItemSetRequest(
            const FVerifyItemSetRequest& From
        );
        ~FVerifyItemSetRequest() = default;

        TSharedPtr<FVerifyItemSetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyItemSetRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyItemSetRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyItemSetRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyItemSetRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifyItemSetRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyItemSetRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FVerifyItemSetRequest> WithCount(const TOptional<int64> Count);
        TSharedPtr<FVerifyItemSetRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyItemSetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyItemSetRequest, ESPMode::ThreadSafe> FVerifyItemSetRequestPtr;
}