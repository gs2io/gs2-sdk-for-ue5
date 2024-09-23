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
    class FUpdateInventoryModelMasterRequest;

    class GS2INVENTORY_API FUpdateInventoryModelMasterRequest final : public TSharedFromThis<FUpdateInventoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<int32> MaxCapacityValue;
        TOptional<bool> ProtectReferencedItemValue;
        
    public:
        
        FUpdateInventoryModelMasterRequest();
        FUpdateInventoryModelMasterRequest(
            const FUpdateInventoryModelMasterRequest& From
        );
        ~FUpdateInventoryModelMasterRequest() = default;

        TSharedPtr<FUpdateInventoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateInventoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateInventoryModelMasterRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FUpdateInventoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateInventoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateInventoryModelMasterRequest> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FUpdateInventoryModelMasterRequest> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FUpdateInventoryModelMasterRequest> WithProtectReferencedItem(const TOptional<bool> ProtectReferencedItem);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialCapacity() const;
        FString GetInitialCapacityString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;
        TOptional<bool> GetProtectReferencedItem() const;
        FString GetProtectReferencedItemString() const;

        static TSharedPtr<FUpdateInventoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateInventoryModelMasterRequest, ESPMode::ThreadSafe> FUpdateInventoryModelMasterRequestPtr;
}