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
    class FVerifyInventoryCurrentMaxCapacityByStampTaskRequest;

    class GS2INVENTORY_API FVerifyInventoryCurrentMaxCapacityByStampTaskRequest final : public TSharedFromThis<FVerifyInventoryCurrentMaxCapacityByStampTaskRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampTaskValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FVerifyInventoryCurrentMaxCapacityByStampTaskRequest();
        FVerifyInventoryCurrentMaxCapacityByStampTaskRequest(
            const FVerifyInventoryCurrentMaxCapacityByStampTaskRequest& From
        );
        ~FVerifyInventoryCurrentMaxCapacityByStampTaskRequest() = default;

        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByStampTaskRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByStampTaskRequest> WithStampTask(const TOptional<FString> StampTask);
        TSharedPtr<FVerifyInventoryCurrentMaxCapacityByStampTaskRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampTask() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FVerifyInventoryCurrentMaxCapacityByStampTaskRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyInventoryCurrentMaxCapacityByStampTaskRequest, ESPMode::ThreadSafe> FVerifyInventoryCurrentMaxCapacityByStampTaskRequestPtr;
}