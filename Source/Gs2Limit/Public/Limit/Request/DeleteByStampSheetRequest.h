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

namespace Gs2::Limit::Request
{
    class FDeleteByStampSheetRequest;

    class GS2LIMIT_API FDeleteByStampSheetRequest final : public TSharedFromThis<FDeleteByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FDeleteByStampSheetRequest();
        FDeleteByStampSheetRequest(
            const FDeleteByStampSheetRequest& From
        );
        ~FDeleteByStampSheetRequest() = default;

        TSharedPtr<FDeleteByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FDeleteByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FDeleteByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteByStampSheetRequest, ESPMode::ThreadSafe> FDeleteByStampSheetRequestPtr;
}