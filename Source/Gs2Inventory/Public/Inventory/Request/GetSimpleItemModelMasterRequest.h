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
    class FGetSimpleItemModelMasterRequest;

    class GS2INVENTORY_API FGetSimpleItemModelMasterRequest final : public TSharedFromThis<FGetSimpleItemModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        
    public:
        
        FGetSimpleItemModelMasterRequest();
        FGetSimpleItemModelMasterRequest(
            const FGetSimpleItemModelMasterRequest& From
        );
        ~FGetSimpleItemModelMasterRequest() = default;

        TSharedPtr<FGetSimpleItemModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSimpleItemModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSimpleItemModelMasterRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetSimpleItemModelMasterRequest> WithItemName(const TOptional<FString> ItemName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;

        static TSharedPtr<FGetSimpleItemModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSimpleItemModelMasterRequest, ESPMode::ThreadSafe> FGetSimpleItemModelMasterRequestPtr;
}