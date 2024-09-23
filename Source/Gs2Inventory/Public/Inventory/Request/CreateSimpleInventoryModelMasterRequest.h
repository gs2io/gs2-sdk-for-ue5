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
    class FCreateSimpleInventoryModelMasterRequest;

    class GS2INVENTORY_API FCreateSimpleInventoryModelMasterRequest final : public TSharedFromThis<FCreateSimpleInventoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        
    public:
        
        FCreateSimpleInventoryModelMasterRequest();
        FCreateSimpleInventoryModelMasterRequest(
            const FCreateSimpleInventoryModelMasterRequest& From
        );
        ~FCreateSimpleInventoryModelMasterRequest() = default;

        TSharedPtr<FCreateSimpleInventoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateSimpleInventoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateSimpleInventoryModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateSimpleInventoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateSimpleInventoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;

        static TSharedPtr<FCreateSimpleInventoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateSimpleInventoryModelMasterRequest, ESPMode::ThreadSafe> FCreateSimpleInventoryModelMasterRequestPtr;
}