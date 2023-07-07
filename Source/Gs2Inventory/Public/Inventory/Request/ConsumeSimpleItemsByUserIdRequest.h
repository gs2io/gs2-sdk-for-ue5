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
#include "../Model/ConsumeCount.h"

namespace Gs2::Inventory::Request
{
    class FConsumeSimpleItemsByUserIdRequest;

    class GS2INVENTORY_API FConsumeSimpleItemsByUserIdRequest final : public TSharedFromThis<FConsumeSimpleItemsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeCount>>> ConsumeCountsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeSimpleItemsByUserIdRequest();
        FConsumeSimpleItemsByUserIdRequest(
            const FConsumeSimpleItemsByUserIdRequest& From
        );
        ~FConsumeSimpleItemsByUserIdRequest() = default;

        TSharedPtr<FConsumeSimpleItemsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeSimpleItemsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeSimpleItemsByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FConsumeSimpleItemsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FConsumeSimpleItemsByUserIdRequest> WithConsumeCounts(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeCount>>> ConsumeCounts);
        TSharedPtr<FConsumeSimpleItemsByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeCount>>> GetConsumeCounts() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeSimpleItemsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeSimpleItemsByUserIdRequest, ESPMode::ThreadSafe> FConsumeSimpleItemsByUserIdRequestPtr;
}