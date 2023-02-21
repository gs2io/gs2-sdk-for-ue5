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

namespace Gs2::Stamina::Request
{
    class FSetRecoverValueByStampSheetRequest;

    class GS2STAMINA_API FSetRecoverValueByStampSheetRequest final : public TSharedFromThis<FSetRecoverValueByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FSetRecoverValueByStampSheetRequest();
        FSetRecoverValueByStampSheetRequest(
            const FSetRecoverValueByStampSheetRequest& From
        );
        ~FSetRecoverValueByStampSheetRequest() = default;

        TSharedPtr<FSetRecoverValueByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetRecoverValueByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FSetRecoverValueByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FSetRecoverValueByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRecoverValueByStampSheetRequest, ESPMode::ThreadSafe> FSetRecoverValueByStampSheetRequestPtr;
}