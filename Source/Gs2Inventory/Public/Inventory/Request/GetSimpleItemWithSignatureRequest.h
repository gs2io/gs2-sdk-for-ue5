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
    class FGetSimpleItemWithSignatureRequest;

    class GS2INVENTORY_API FGetSimpleItemWithSignatureRequest final : public TSharedFromThis<FGetSimpleItemWithSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetSimpleItemWithSignatureRequest();
        FGetSimpleItemWithSignatureRequest(
            const FGetSimpleItemWithSignatureRequest& From
        );
        ~FGetSimpleItemWithSignatureRequest() = default;

        TSharedPtr<FGetSimpleItemWithSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSimpleItemWithSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSimpleItemWithSignatureRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetSimpleItemWithSignatureRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetSimpleItemWithSignatureRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FGetSimpleItemWithSignatureRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetSimpleItemWithSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSimpleItemWithSignatureRequest, ESPMode::ThreadSafe> FGetSimpleItemWithSignatureRequestPtr;
}