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
    class FVerifyInventoryCurrentMaxCapacityRequest;

    class GS2INVENTORY_API FVerifyInventoryCurrentMaxCapacityRequest final : public TSharedFromThis<FVerifyInventoryCurrentMaxCapacityRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CurrentInventoryMaxCapacityValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyInventoryCurrentMaxCapacityRequest();
        FVerifyInventoryCurrentMaxCapacityRequest(
            const FVerifyInventoryCurrentMaxCapacityRequest& From
        );
        ~FVerifyInventoryCurrentMaxCapacityRequest() = default;

        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithCurrentInventoryMaxCapacity(const TOptional<int32> CurrentInventoryMaxCapacity);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCurrentInventoryMaxCapacity() const;
        FString GetCurrentInventoryMaxCapacityString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequestPtr;
}