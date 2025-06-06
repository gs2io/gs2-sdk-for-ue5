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
    class FDeleteReferenceOfByUserIdRequest;

    class GS2INVENTORY_API FDeleteReferenceOfByUserIdRequest final : public TSharedFromThis<FDeleteReferenceOfByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> ReferenceOfValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteReferenceOfByUserIdRequest();
        FDeleteReferenceOfByUserIdRequest(
            const FDeleteReferenceOfByUserIdRequest& From
        );
        ~FDeleteReferenceOfByUserIdRequest() = default;

        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithReferenceOf(const TOptional<FString> ReferenceOf);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteReferenceOfByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetReferenceOf() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteReferenceOfByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteReferenceOfByUserIdRequest> FDeleteReferenceOfByUserIdRequestPtr;
}