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

namespace Gs2::Experience::Request
{
    class FAddRankCapByStampSheetRequest;

    class GS2EXPERIENCE_API FAddRankCapByStampSheetRequest final : public TSharedFromThis<FAddRankCapByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FAddRankCapByStampSheetRequest();
        FAddRankCapByStampSheetRequest(
            const FAddRankCapByStampSheetRequest& From
        );
        ~FAddRankCapByStampSheetRequest() = default;

        TSharedPtr<FAddRankCapByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddRankCapByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FAddRankCapByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FAddRankCapByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddRankCapByStampSheetRequest> FAddRankCapByStampSheetRequestPtr;
}