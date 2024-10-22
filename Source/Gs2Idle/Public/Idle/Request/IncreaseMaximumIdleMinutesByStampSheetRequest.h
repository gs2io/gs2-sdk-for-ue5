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

namespace Gs2::Idle::Request
{
    class FIncreaseMaximumIdleMinutesByStampSheetRequest;

    class GS2IDLE_API FIncreaseMaximumIdleMinutesByStampSheetRequest final : public TSharedFromThis<FIncreaseMaximumIdleMinutesByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FIncreaseMaximumIdleMinutesByStampSheetRequest();
        FIncreaseMaximumIdleMinutesByStampSheetRequest(
            const FIncreaseMaximumIdleMinutesByStampSheetRequest& From
        );
        ~FIncreaseMaximumIdleMinutesByStampSheetRequest() = default;

        TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncreaseMaximumIdleMinutesByStampSheetRequest> FIncreaseMaximumIdleMinutesByStampSheetRequestPtr;
}