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
    class FSetFormByStampSheetRequest;

    class GS2FORMATION_API FSetFormByStampSheetRequest final : public TSharedFromThis<FSetFormByStampSheetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FSetFormByStampSheetRequest();
        FSetFormByStampSheetRequest(
            const FSetFormByStampSheetRequest& From
        );
        ~FSetFormByStampSheetRequest() = default;

        TSharedPtr<FSetFormByStampSheetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetFormByStampSheetRequest> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FSetFormByStampSheetRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FSetFormByStampSheetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetFormByStampSheetRequest> FSetFormByStampSheetRequestPtr;
}