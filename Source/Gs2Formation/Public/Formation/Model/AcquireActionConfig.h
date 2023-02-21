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
#include "Config.h"

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FAcquireActionConfig final : public TSharedFromThis<FAcquireActionConfig>
    {
        TOptional<FString> NameValue;
        TSharedPtr<TArray<TSharedPtr<FConfig>>> ConfigValue;

    public:
        FAcquireActionConfig();
        FAcquireActionConfig(
            const FAcquireActionConfig& From
        );
        ~FAcquireActionConfig() = default;

        TSharedPtr<FAcquireActionConfig> WithName(const TOptional<FString> Name);
        TSharedPtr<FAcquireActionConfig> WithConfig(const TSharedPtr<TArray<TSharedPtr<FConfig>>> Config);

        TOptional<FString> GetName() const;
        TSharedPtr<TArray<TSharedPtr<FConfig>>> GetConfig() const;


        static TSharedPtr<FAcquireActionConfig> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAcquireActionConfig, ESPMode::ThreadSafe> FAcquireActionConfigPtr;
}