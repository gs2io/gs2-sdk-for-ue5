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
    class FVerifyInventoryCurrentMaxCapacityByUserIdRequest;

    class GS2INVENTORY_API FVerifyInventoryCurrentMaxCapacityByUserIdRequest final : public TSharedFromThis<FVerifyInventoryCurrentMaxCapacityByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CurrentInventoryMaxCapacityValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyInventoryCurrentMaxCapacityByUserIdRequest();
        FVerifyInventoryCurrentMaxCapacityByUserIdRequest(
            const FVerifyInventoryCurrentMaxCapacityByUserIdRequest& From
        );
        ~FVerifyInventoryCurrentMaxCapacityByUserIdRequest() = default;

        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithCurrentInventoryMaxCapacity(const TOptional<int32> CurrentInventoryMaxCapacity);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCurrentInventoryMaxCapacity() const;
        FString GetCurrentInventoryMaxCapacityString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest, ESPMode::ThreadSafe> FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr;
}