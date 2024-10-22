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
    class FGetSimpleInventoryModelRequest;

    class GS2INVENTORY_API FGetSimpleInventoryModelRequest final : public TSharedFromThis<FGetSimpleInventoryModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        
    public:
        
        FGetSimpleInventoryModelRequest();
        FGetSimpleInventoryModelRequest(
            const FGetSimpleInventoryModelRequest& From
        );
        ~FGetSimpleInventoryModelRequest() = default;

        TSharedPtr<FGetSimpleInventoryModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSimpleInventoryModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSimpleInventoryModelRequest> WithInventoryName(const TOptional<FString> InventoryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;

        static TSharedPtr<FGetSimpleInventoryModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSimpleInventoryModelRequest> FGetSimpleInventoryModelRequestPtr;
}