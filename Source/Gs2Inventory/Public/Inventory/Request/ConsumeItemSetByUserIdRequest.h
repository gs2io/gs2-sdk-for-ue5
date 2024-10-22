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
    class FConsumeItemSetByUserIdRequest;

    class GS2INVENTORY_API FConsumeItemSetByUserIdRequest final : public TSharedFromThis<FConsumeItemSetByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<int64> ConsumeCountValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeItemSetByUserIdRequest();
        FConsumeItemSetByUserIdRequest(
            const FConsumeItemSetByUserIdRequest& From
        );
        ~FConsumeItemSetByUserIdRequest() = default;

        TSharedPtr<FConsumeItemSetByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithConsumeCount(const TOptional<int64> ConsumeCount);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FConsumeItemSetByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<int64> GetConsumeCount() const;
        FString GetConsumeCountString() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeItemSetByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequestPtr;
}