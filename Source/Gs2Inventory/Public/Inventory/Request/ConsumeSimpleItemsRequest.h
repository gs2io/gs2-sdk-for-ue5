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
#include "../Model/ConsumeCount.h"

namespace Gs2::Inventory::Request
{
    class FConsumeSimpleItemsRequest;

    class GS2INVENTORY_API FConsumeSimpleItemsRequest final : public TSharedFromThis<FConsumeSimpleItemsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeCount>>> ConsumeCountsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeSimpleItemsRequest();
        FConsumeSimpleItemsRequest(
            const FConsumeSimpleItemsRequest& From
        );
        ~FConsumeSimpleItemsRequest() = default;

        TSharedPtr<FConsumeSimpleItemsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeSimpleItemsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeSimpleItemsRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FConsumeSimpleItemsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FConsumeSimpleItemsRequest> WithConsumeCounts(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeCount>>> ConsumeCounts);
        TSharedPtr<FConsumeSimpleItemsRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeCount>>> GetConsumeCounts() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeSimpleItemsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeSimpleItemsRequest> FConsumeSimpleItemsRequestPtr;
}