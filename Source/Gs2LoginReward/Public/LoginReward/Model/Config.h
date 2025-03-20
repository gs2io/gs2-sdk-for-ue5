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

namespace Gs2::LoginReward::Model
{
    class GS2LOGINREWARD_API FConfig final : public FGs2Object, public TSharedFromThis<FConfig>
    {
        TOptional<FString> KeyValue;
        TOptional<FString> ValueValue;

    public:
        FConfig();
        FConfig(
            const FConfig& From
        );
        virtual ~FConfig() override = default;

        TSharedPtr<FConfig> WithKey(const TOptional<FString> Key);
        TSharedPtr<FConfig> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetKey() const;
        TOptional<FString> GetValue() const;


        static TSharedPtr<FConfig> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FConfig, ESPMode::ThreadSafe> FConfigPtr;
}