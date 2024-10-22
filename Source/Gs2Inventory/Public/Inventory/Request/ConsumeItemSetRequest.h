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
    class FConsumeItemSetRequest;

    class GS2INVENTORY_API FConsumeItemSetRequest final : public TSharedFromThis<FConsumeItemSetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<int64> ConsumeCountValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeItemSetRequest();
        FConsumeItemSetRequest(
            const FConsumeItemSetRequest& From
        );
        ~FConsumeItemSetRequest() = default;

        TSharedPtr<FConsumeItemSetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeItemSetRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeItemSetRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FConsumeItemSetRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FConsumeItemSetRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FConsumeItemSetRequest> WithConsumeCount(const TOptional<int64> ConsumeCount);
        TSharedPtr<FConsumeItemSetRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FConsumeItemSetRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<int64> GetConsumeCount() const;
        FString GetConsumeCountString() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeItemSetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequestPtr;
}