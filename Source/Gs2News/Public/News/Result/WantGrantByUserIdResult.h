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
#include "../Model/SetCookieRequestEntry.h"

namespace Gs2::News::Result
{
    class GS2NEWS_API FWantGrantByUserIdResult final : public TSharedFromThis<FWantGrantByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FSetCookieRequestEntry>>> ItemsValue;
        TOptional<FString> BrowserUrlValue;
        TOptional<FString> ZipUrlValue;
        
    public:
        
        FWantGrantByUserIdResult();
        FWantGrantByUserIdResult(
            const FWantGrantByUserIdResult& From
        );
        ~FWantGrantByUserIdResult() = default;

        TSharedPtr<FWantGrantByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FSetCookieRequestEntry>>> Items);
        TSharedPtr<FWantGrantByUserIdResult> WithBrowserUrl(const TOptional<FString> BrowserUrl);
        TSharedPtr<FWantGrantByUserIdResult> WithZipUrl(const TOptional<FString> ZipUrl);

        TSharedPtr<TArray<TSharedPtr<Model::FSetCookieRequestEntry>>> GetItems() const;
        TOptional<FString> GetBrowserUrl() const;
        TOptional<FString> GetZipUrl() const;

        static TSharedPtr<FWantGrantByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FWantGrantByUserIdResult, ESPMode::ThreadSafe> FWantGrantByUserIdResultPtr;
}