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
    class FCreateInventoryModelMasterRequest;

    class GS2INVENTORY_API FCreateInventoryModelMasterRequest final : public TSharedFromThis<FCreateInventoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<int32> MaxCapacityValue;
        TOptional<bool> ProtectReferencedItemValue;
        
    public:
        
        FCreateInventoryModelMasterRequest();
        FCreateInventoryModelMasterRequest(
            const FCreateInventoryModelMasterRequest& From
        );
        ~FCreateInventoryModelMasterRequest() = default;

        TSharedPtr<FCreateInventoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateInventoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateInventoryModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateInventoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateInventoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateInventoryModelMasterRequest> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FCreateInventoryModelMasterRequest> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FCreateInventoryModelMasterRequest> WithProtectReferencedItem(const TOptional<bool> ProtectReferencedItem);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialCapacity() const;
        FString GetInitialCapacityString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;
        TOptional<bool> GetProtectReferencedItem() const;
        FString GetProtectReferencedItemString() const;

        static TSharedPtr<FCreateInventoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateInventoryModelMasterRequest, ESPMode::ThreadSafe> FCreateInventoryModelMasterRequestPtr;
}