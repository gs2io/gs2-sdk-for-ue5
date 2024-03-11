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
    class FVerifyReferenceOfByUserIdRequest;

    class GS2INVENTORY_API FVerifyReferenceOfByUserIdRequest final : public TSharedFromThis<FVerifyReferenceOfByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> ItemSetNameValue;
        TOptional<FString> ReferenceOfValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyReferenceOfByUserIdRequest();
        FVerifyReferenceOfByUserIdRequest(
            const FVerifyReferenceOfByUserIdRequest& From
        );
        ~FVerifyReferenceOfByUserIdRequest() = default;

        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithItemSetName(const TOptional<FString> ItemSetName);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithReferenceOf(const TOptional<FString> ReferenceOf);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyReferenceOfByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetItemSetName() const;
        TOptional<FString> GetReferenceOf() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyReferenceOfByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyReferenceOfByUserIdRequest, ESPMode::ThreadSafe> FVerifyReferenceOfByUserIdRequestPtr;
}