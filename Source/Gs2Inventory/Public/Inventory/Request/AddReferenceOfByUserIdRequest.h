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
    class FAddReferenceOfByUserIdRequest;

    class GS2INVENTORY_API FAddReferenceOfByUserIdRequest final : public TSharedFromThis<FAddReferenceOfByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> ReferenceOfValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddReferenceOfByUserIdRequest();
        FAddReferenceOfByUserIdRequest(
            const FAddReferenceOfByUserIdRequest& From
        );
        ~FAddReferenceOfByUserIdRequest() = default;

        TSharedPtr<FAddReferenceOfByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddReferenceOfByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddReferenceOfByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FAddReferenceOfByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddReferenceOfByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FAddReferenceOfByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FAddReferenceOfByUserIdRequest> WithReferenceOf(const TOptional<FString> ReferenceOf);
        TSharedPtr<FAddReferenceOfByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetReferenceOf() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddReferenceOfByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddReferenceOfByUserIdRequest, ESPMode::ThreadSafe> FAddReferenceOfByUserIdRequestPtr;
}