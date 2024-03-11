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
    class FGetSimpleItemWithSignatureByUserIdRequest;

    class GS2INVENTORY_API FGetSimpleItemWithSignatureByUserIdRequest final : public TSharedFromThis<FGetSimpleItemWithSignatureByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetSimpleItemWithSignatureByUserIdRequest();
        FGetSimpleItemWithSignatureByUserIdRequest(
            const FGetSimpleItemWithSignatureByUserIdRequest& From
        );
        ~FGetSimpleItemWithSignatureByUserIdRequest() = default;

        TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSimpleItemWithSignatureByUserIdRequest, ESPMode::ThreadSafe> FGetSimpleItemWithSignatureByUserIdRequestPtr;
}