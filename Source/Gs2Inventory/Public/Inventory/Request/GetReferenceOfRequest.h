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
    class FGetReferenceOfRequest;

    class GS2INVENTORY_API FGetReferenceOfRequest final : public TSharedFromThis<FGetReferenceOfRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> ReferenceOfValue;
        
    public:
        
        FGetReferenceOfRequest();
        FGetReferenceOfRequest(
            const FGetReferenceOfRequest& From
        );
        ~FGetReferenceOfRequest() = default;

        TSharedPtr<FGetReferenceOfRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetReferenceOfRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetReferenceOfRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetReferenceOfRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetReferenceOfRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FGetReferenceOfRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FGetReferenceOfRequest> WithReferenceOf(const TOptional<FString> ReferenceOf);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetReferenceOf() const;

        static TSharedPtr<FGetReferenceOfRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetReferenceOfRequest> FGetReferenceOfRequestPtr;
}