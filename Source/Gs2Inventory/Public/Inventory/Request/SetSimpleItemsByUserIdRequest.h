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
#include "../Model/HeldCount.h"

namespace Gs2::Inventory::Request
{
    class FSetSimpleItemsByUserIdRequest;

    class GS2INVENTORY_API FSetSimpleItemsByUserIdRequest final : public TSharedFromThis<FSetSimpleItemsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FHeldCount>>> CountsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetSimpleItemsByUserIdRequest();
        FSetSimpleItemsByUserIdRequest(
            const FSetSimpleItemsByUserIdRequest& From
        );
        ~FSetSimpleItemsByUserIdRequest() = default;

        TSharedPtr<FSetSimpleItemsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetSimpleItemsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetSimpleItemsByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FSetSimpleItemsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetSimpleItemsByUserIdRequest> WithCounts(const TSharedPtr<TArray<TSharedPtr<Model::FHeldCount>>> Counts);
        TSharedPtr<FSetSimpleItemsByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FHeldCount>>> GetCounts() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetSimpleItemsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetSimpleItemsByUserIdRequest, ESPMode::ThreadSafe> FSetSimpleItemsByUserIdRequestPtr;
}