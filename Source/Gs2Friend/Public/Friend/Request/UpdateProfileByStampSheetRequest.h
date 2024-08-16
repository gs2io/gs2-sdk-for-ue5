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

namespace Gs2::Friend::Request
{
    class FUpdateProfileByStampSheetRequest;

    class GS2FRIEND_API FUpdateProfileByStampSheetRequest final : public TSharedFromThis<FUpdateProfileByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FUpdateProfileByStampSheetRequest();
        FUpdateProfileByStampSheetRequest(
            const FUpdateProfileByStampSheetRequest& From
        );
        ~FUpdateProfileByStampSheetRequest() = default;

        TSharedPtr<FUpdateProfileByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateProfileByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FUpdateProfileByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FUpdateProfileByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateProfileByStampSheetRequest, ESPMode::ThreadSafe> FUpdateProfileByStampSheetRequestPtr;
}