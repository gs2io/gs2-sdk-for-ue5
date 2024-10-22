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

namespace Gs2::Formation::Request
{
    class FAcquireActionToFormPropertiesByStampSheetRequest;

    class GS2FORMATION_API FAcquireActionToFormPropertiesByStampSheetRequest final : public TSharedFromThis<FAcquireActionToFormPropertiesByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FAcquireActionToFormPropertiesByStampSheetRequest();
        FAcquireActionToFormPropertiesByStampSheetRequest(
            const FAcquireActionToFormPropertiesByStampSheetRequest& From
        );
        ~FAcquireActionToFormPropertiesByStampSheetRequest() = default;

        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FAcquireActionToFormPropertiesByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireActionToFormPropertiesByStampSheetRequest> FAcquireActionToFormPropertiesByStampSheetRequestPtr;
}