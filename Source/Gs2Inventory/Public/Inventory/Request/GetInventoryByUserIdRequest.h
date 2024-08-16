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
    class FGetInventoryByUserIdRequest;

    class GS2INVENTORY_API FGetInventoryByUserIdRequest final : public TSharedFromThis<FGetInventoryByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetInventoryByUserIdRequest();
        FGetInventoryByUserIdRequest(
            const FGetInventoryByUserIdRequest& From
        );
        ~FGetInventoryByUserIdRequest() = default;

        TSharedPtr<FGetInventoryByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetInventoryByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetInventoryByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetInventoryByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetInventoryByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetInventoryByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetInventoryByUserIdRequest> FGetInventoryByUserIdRequestPtr;
}