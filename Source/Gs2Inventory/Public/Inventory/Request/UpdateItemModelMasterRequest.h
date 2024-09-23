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
    class FUpdateItemModelMasterRequest;

    class GS2INVENTORY_API FUpdateItemModelMasterRequest final : public TSharedFromThis<FUpdateItemModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> StackingLimitValue;
        TOptional<bool> AllowMultipleStacksValue;
        TOptional<int32> SortValueValue;
        
    public:
        
        FUpdateItemModelMasterRequest();
        FUpdateItemModelMasterRequest(
            const FUpdateItemModelMasterRequest& From
        );
        ~FUpdateItemModelMasterRequest() = default;

        TSharedPtr<FUpdateItemModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateItemModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateItemModelMasterRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FUpdateItemModelMasterRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FUpdateItemModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateItemModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateItemModelMasterRequest> WithStackingLimit(const TOptional<int64> StackingLimit);
        TSharedPtr<FUpdateItemModelMasterRequest> WithAllowMultipleStacks(const TOptional<bool> AllowMultipleStacks);
        TSharedPtr<FUpdateItemModelMasterRequest> WithSortValue(const TOptional<int32> SortValue);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetStackingLimit() const;
        FString GetStackingLimitString() const;
        TOptional<bool> GetAllowMultipleStacks() const;
        FString GetAllowMultipleStacksString() const;
        TOptional<int32> GetSortValue() const;
        FString GetSortValueString() const;

        static TSharedPtr<FUpdateItemModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateItemModelMasterRequest, ESPMode::ThreadSafe> FUpdateItemModelMasterRequestPtr;
}