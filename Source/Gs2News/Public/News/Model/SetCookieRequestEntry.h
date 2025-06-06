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
#include "Core/Gs2Object.h"

namespace Gs2::News::Model
{
    class GS2NEWS_API FSetCookieRequestEntry final : public FGs2Object, public TSharedFromThis<FSetCookieRequestEntry>
    {
        TOptional<FString> KeyValue;
        TOptional<FString> ValueValue;

    public:
        FSetCookieRequestEntry();
        FSetCookieRequestEntry(
            const FSetCookieRequestEntry& From
        );
        virtual ~FSetCookieRequestEntry() override = default;

        TSharedPtr<FSetCookieRequestEntry> WithKey(const TOptional<FString> Key);
        TSharedPtr<FSetCookieRequestEntry> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetKey() const;
        TOptional<FString> GetValue() const;


        static TSharedPtr<FSetCookieRequestEntry> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSetCookieRequestEntry, ESPMode::ThreadSafe> FSetCookieRequestEntryPtr;
}