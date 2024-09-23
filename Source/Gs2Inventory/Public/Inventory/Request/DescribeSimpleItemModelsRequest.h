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
    class FDescribeSimpleItemModelsRequest;

    class GS2INVENTORY_API FDescribeSimpleItemModelsRequest final : public TSharedFromThis<FDescribeSimpleItemModelsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        
    public:
        
        FDescribeSimpleItemModelsRequest();
        FDescribeSimpleItemModelsRequest(
            const FDescribeSimpleItemModelsRequest& From
        );
        ~FDescribeSimpleItemModelsRequest() = default;

        TSharedPtr<FDescribeSimpleItemModelsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeSimpleItemModelsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeSimpleItemModelsRequest> WithInventoryName(const TOptional<FString> InventoryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;

        static TSharedPtr<FDescribeSimpleItemModelsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeSimpleItemModelsRequest, ESPMode::ThreadSafe> FDescribeSimpleItemModelsRequestPtr;
}