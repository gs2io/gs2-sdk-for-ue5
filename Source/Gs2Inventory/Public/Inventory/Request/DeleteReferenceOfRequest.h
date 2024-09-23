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
    class FDeleteReferenceOfRequest;

    class GS2INVENTORY_API FDeleteReferenceOfRequest final : public TSharedFromThis<FDeleteReferenceOfRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> ReferenceOfValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteReferenceOfRequest();
        FDeleteReferenceOfRequest(
            const FDeleteReferenceOfRequest& From
        );
        ~FDeleteReferenceOfRequest() = default;

        TSharedPtr<FDeleteReferenceOfRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteReferenceOfRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteReferenceOfRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FDeleteReferenceOfRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteReferenceOfRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FDeleteReferenceOfRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FDeleteReferenceOfRequest> WithReferenceOf(const TOptional<FString> ReferenceOf);
        TSharedPtr<FDeleteReferenceOfRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetReferenceOf() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteReferenceOfRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteReferenceOfRequest, ESPMode::ThreadSafe> FDeleteReferenceOfRequestPtr;
}