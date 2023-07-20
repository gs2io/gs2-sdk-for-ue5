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

namespace Gs2::Enchant::Model
{
    class GS2ENCHANT_API FRarityParameterValue final : public Gs2Object, public TSharedFromThis<FRarityParameterValue>
    {
        TOptional<FString> NameValue;
        TOptional<FString> ResourceNameValue;
        TOptional<int64> ResourceValueValue;

    public:
        FRarityParameterValue();
        FRarityParameterValue(
            const FRarityParameterValue& From
        );
        virtual ~FRarityParameterValue() override = default;

        TSharedPtr<FRarityParameterValue> WithName(const TOptional<FString> Name);
        TSharedPtr<FRarityParameterValue> WithResourceName(const TOptional<FString> ResourceName);
        TSharedPtr<FRarityParameterValue> WithResourceValue(const TOptional<int64> ResourceValue);

        TOptional<FString> GetName() const;
        TOptional<FString> GetResourceName() const;
        TOptional<int64> GetResourceValue() const;
        FString GetResourceValueString() const;


        static TSharedPtr<FRarityParameterValue> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRarityParameterValue, ESPMode::ThreadSafe> FRarityParameterValuePtr;
}