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

namespace Gs2::Dictionary::Request
{
    class FAddEntriesByStampSheetRequest;

    class GS2DICTIONARY_API FAddEntriesByStampSheetRequest final : public TSharedFromThis<FAddEntriesByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FAddEntriesByStampSheetRequest();
        FAddEntriesByStampSheetRequest(
            const FAddEntriesByStampSheetRequest& From
        );
        ~FAddEntriesByStampSheetRequest() = default;

        TSharedPtr<FAddEntriesByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddEntriesByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FAddEntriesByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FAddEntriesByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddEntriesByStampSheetRequest> FAddEntriesByStampSheetRequestPtr;
}