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
    class FUpdateBigInventoryModelMasterRequest;

    class GS2INVENTORY_API FUpdateBigInventoryModelMasterRequest final : public TSharedFromThis<FUpdateBigInventoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        
    public:
        
        FUpdateBigInventoryModelMasterRequest();
        FUpdateBigInventoryModelMasterRequest(
            const FUpdateBigInventoryModelMasterRequest& From
        );
        ~FUpdateBigInventoryModelMasterRequest() = default;

        TSharedPtr<FUpdateBigInventoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateBigInventoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateBigInventoryModelMasterRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FUpdateBigInventoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateBigInventoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;

        static TSharedPtr<FUpdateBigInventoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateBigInventoryModelMasterRequest> FUpdateBigInventoryModelMasterRequestPtr;
}