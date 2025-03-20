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

namespace Gs2::Log::Model
{
    class GS2LOG_API FInGameLogTag final : public FGs2Object, public TSharedFromThis<FInGameLogTag>
    {
        TOptional<FString> KeyValue;
        TOptional<FString> ValueValue;

    public:
        FInGameLogTag();
        FInGameLogTag(
            const FInGameLogTag& From
        );
        virtual ~FInGameLogTag() override = default;

        TSharedPtr<FInGameLogTag> WithKey(const TOptional<FString> Key);
        TSharedPtr<FInGameLogTag> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetKey() const;
        TOptional<FString> GetValue() const;


        static TSharedPtr<FInGameLogTag> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FInGameLogTag, ESPMode::ThreadSafe> FInGameLogTagPtr;
}