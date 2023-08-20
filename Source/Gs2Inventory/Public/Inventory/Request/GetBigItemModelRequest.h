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
    class FGetBigItemModelRequest;

    class GS2INVENTORY_API FGetBigItemModelRequest final : public TSharedFromThis<FGetBigItemModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        
    public:
        
        FGetBigItemModelRequest();
        FGetBigItemModelRequest(
            const FGetBigItemModelRequest& From
        );
        ~FGetBigItemModelRequest() = default;

        TSharedPtr<FGetBigItemModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBigItemModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBigItemModelRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetBigItemModelRequest> WithItemName(const TOptional<FString> ItemName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;

        static TSharedPtr<FGetBigItemModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBigItemModelRequest, ESPMode::ThreadSafe> FGetBigItemModelRequestPtr;
}