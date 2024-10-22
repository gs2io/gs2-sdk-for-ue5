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
    class FConsumeBigItemByUserIdRequest;

    class GS2INVENTORY_API FConsumeBigItemByUserIdRequest final : public TSharedFromThis<FConsumeBigItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ConsumeCountValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeBigItemByUserIdRequest();
        FConsumeBigItemByUserIdRequest(
            const FConsumeBigItemByUserIdRequest& From
        );
        ~FConsumeBigItemByUserIdRequest() = default;

        TSharedPtr<FConsumeBigItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeBigItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeBigItemByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FConsumeBigItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FConsumeBigItemByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FConsumeBigItemByUserIdRequest> WithConsumeCount(const TOptional<FString> ConsumeCount);
        TSharedPtr<FConsumeBigItemByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FConsumeBigItemByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetConsumeCount() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeBigItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeBigItemByUserIdRequest> FConsumeBigItemByUserIdRequestPtr;
}