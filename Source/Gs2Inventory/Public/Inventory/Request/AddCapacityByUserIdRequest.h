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
    class FAddCapacityByUserIdRequest;

    class GS2INVENTORY_API FAddCapacityByUserIdRequest final : public TSharedFromThis<FAddCapacityByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> AddCapacityValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddCapacityByUserIdRequest();
        FAddCapacityByUserIdRequest(
            const FAddCapacityByUserIdRequest& From
        );
        ~FAddCapacityByUserIdRequest() = default;

        TSharedPtr<FAddCapacityByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddCapacityByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddCapacityByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FAddCapacityByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddCapacityByUserIdRequest> WithAddCapacityValue(const TOptional<int32> AddCapacityValue);
        TSharedPtr<FAddCapacityByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAddCapacityByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetAddCapacityValue() const;
        FString GetAddCapacityValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddCapacityByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddCapacityByUserIdRequest> FAddCapacityByUserIdRequestPtr;
}