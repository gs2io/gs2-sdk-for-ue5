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

namespace Gs2::Enhance::Request
{
    class FDirectEnhanceByStampSheetRequest;

    class GS2ENHANCE_API FDirectEnhanceByStampSheetRequest final : public TSharedFromThis<FDirectEnhanceByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FDirectEnhanceByStampSheetRequest();
        FDirectEnhanceByStampSheetRequest(
            const FDirectEnhanceByStampSheetRequest& From
        );
        ~FDirectEnhanceByStampSheetRequest() = default;

        TSharedPtr<FDirectEnhanceByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDirectEnhanceByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FDirectEnhanceByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FDirectEnhanceByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDirectEnhanceByStampSheetRequest> FDirectEnhanceByStampSheetRequestPtr;
}