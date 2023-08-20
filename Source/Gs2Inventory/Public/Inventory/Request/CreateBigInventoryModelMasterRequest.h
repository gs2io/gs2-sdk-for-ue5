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
    class FCreateBigInventoryModelMasterRequest;

    class GS2INVENTORY_API FCreateBigInventoryModelMasterRequest final : public TSharedFromThis<FCreateBigInventoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        
    public:
        
        FCreateBigInventoryModelMasterRequest();
        FCreateBigInventoryModelMasterRequest(
            const FCreateBigInventoryModelMasterRequest& From
        );
        ~FCreateBigInventoryModelMasterRequest() = default;

        TSharedPtr<FCreateBigInventoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateBigInventoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateBigInventoryModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateBigInventoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateBigInventoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;

        static TSharedPtr<FCreateBigInventoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateBigInventoryModelMasterRequest, ESPMode::ThreadSafe> FCreateBigInventoryModelMasterRequestPtr;
}