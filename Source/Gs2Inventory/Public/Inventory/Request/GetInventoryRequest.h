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
    class FGetInventoryRequest;

    class GS2INVENTORY_API FGetInventoryRequest final : public TSharedFromThis<FGetInventoryRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetInventoryRequest();
        FGetInventoryRequest(
            const FGetInventoryRequest& From
        );
        ~FGetInventoryRequest() = default;

        TSharedPtr<FGetInventoryRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetInventoryRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetInventoryRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetInventoryRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetInventoryRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetInventoryRequest, ESPMode::ThreadSafe> FGetInventoryRequestPtr;
}