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
    class FSetCapacityByUserIdRequest;

    class GS2INVENTORY_API FSetCapacityByUserIdRequest final : public TSharedFromThis<FSetCapacityByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> NewCapacityValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetCapacityByUserIdRequest();
        FSetCapacityByUserIdRequest(
            const FSetCapacityByUserIdRequest& From
        );
        ~FSetCapacityByUserIdRequest() = default;

        TSharedPtr<FSetCapacityByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetCapacityByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetCapacityByUserIdRequest> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FSetCapacityByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetCapacityByUserIdRequest> WithNewCapacityValue(const TOptional<int32> NewCapacityValue);
        TSharedPtr<FSetCapacityByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetNewCapacityValue() const;
        FString GetNewCapacityValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetCapacityByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetCapacityByUserIdRequest, ESPMode::ThreadSafe> FSetCapacityByUserIdRequestPtr;
}