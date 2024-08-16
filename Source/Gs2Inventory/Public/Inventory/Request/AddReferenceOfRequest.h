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
    class FAddReferenceOfRequest;

    class GS2INVENTORY_API FAddReferenceOfRequest final : public TSharedFromThis<FAddReferenceOfRequest>
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
        
        FAddReferenceOfRequest();
        FAddReferenceOfRequest(
            const FAddReferenceOfRequest& From
        );
        ~FAddReferenceOfRequest() = default;

        TSharedPtr<FAddReferenceOfRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddReferenceOfRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddReferenceOfRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FAddReferenceOfRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FAddReferenceOfRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FAddReferenceOfRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FAddReferenceOfRequest> WithReferenceOf(const TOptional<FString> ReferenceOf);
        TSharedPtr<FAddReferenceOfRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetReferenceOf() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddReferenceOfRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddReferenceOfRequest> FAddReferenceOfRequestPtr;
}