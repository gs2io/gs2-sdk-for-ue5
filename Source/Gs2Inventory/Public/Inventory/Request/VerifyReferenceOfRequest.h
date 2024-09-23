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
    class FVerifyReferenceOfRequest;

    class GS2INVENTORY_API FVerifyReferenceOfRequest final : public TSharedFromThis<FVerifyReferenceOfRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> ReferenceOfValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyReferenceOfRequest();
        FVerifyReferenceOfRequest(
            const FVerifyReferenceOfRequest& From
        );
        ~FVerifyReferenceOfRequest() = default;

        TSharedPtr<FVerifyReferenceOfRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyReferenceOfRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyReferenceOfRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyReferenceOfRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyReferenceOfRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifyReferenceOfRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FVerifyReferenceOfRequest> WithReferenceOf(const TOptional<FString> ReferenceOf);
        TSharedPtr<FVerifyReferenceOfRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyReferenceOfRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetReferenceOf() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyReferenceOfRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyReferenceOfRequest, ESPMode::ThreadSafe> FVerifyReferenceOfRequestPtr;
}