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
    class FDescribeReferenceOfByUserIdRequest;

    class GS2INVENTORY_API FDescribeReferenceOfByUserIdRequest final : public TSharedFromThis<FDescribeReferenceOfByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        
    public:
        
        FDescribeReferenceOfByUserIdRequest();
        FDescribeReferenceOfByUserIdRequest(
            const FDescribeReferenceOfByUserIdRequest& From
        );
        ~FDescribeReferenceOfByUserIdRequest() = default;

        TSharedPtr<FDescribeReferenceOfByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeReferenceOfByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeReferenceOfByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FDescribeReferenceOfByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeReferenceOfByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FDescribeReferenceOfByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;

        static TSharedPtr<FDescribeReferenceOfByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeReferenceOfByUserIdRequest, ESPMode::ThreadSafe> FDescribeReferenceOfByUserIdRequestPtr;
}