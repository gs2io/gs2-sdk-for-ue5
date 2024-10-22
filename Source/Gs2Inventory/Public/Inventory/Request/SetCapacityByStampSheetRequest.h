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
    class FSetCapacityByStampSheetRequest;

    class GS2INVENTORY_API FSetCapacityByStampSheetRequest final : public TSharedFromThis<FSetCapacityByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FSetCapacityByStampSheetRequest();
        FSetCapacityByStampSheetRequest(
            const FSetCapacityByStampSheetRequest& From
        );
        ~FSetCapacityByStampSheetRequest() = default;

        TSharedPtr<FSetCapacityByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetCapacityByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FSetCapacityByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FSetCapacityByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetCapacityByStampSheetRequest> FSetCapacityByStampSheetRequestPtr;
}