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
    class FAcquireSimpleItemsByStampSheetRequest;

    class GS2INVENTORY_API FAcquireSimpleItemsByStampSheetRequest final : public TSharedFromThis<FAcquireSimpleItemsByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FAcquireSimpleItemsByStampSheetRequest();
        FAcquireSimpleItemsByStampSheetRequest(
            const FAcquireSimpleItemsByStampSheetRequest& From
        );
        ~FAcquireSimpleItemsByStampSheetRequest() = default;

        TSharedPtr<FAcquireSimpleItemsByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireSimpleItemsByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FAcquireSimpleItemsByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FAcquireSimpleItemsByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireSimpleItemsByStampSheetRequest, ESPMode::ThreadSafe> FAcquireSimpleItemsByStampSheetRequestPtr;
}