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
    class GS2ENCHANT_API FBalanceParameterValue final : public Gs2Object, public TSharedFromThis<FBalanceParameterValue>
    {
        TOptional<FString> NameValue;
        TOptional<int64> ValueValue;

    public:
        FBalanceParameterValue();
        FBalanceParameterValue(
            const FBalanceParameterValue& From
        );
        virtual ~FBalanceParameterValue() override = default;

        TSharedPtr<FBalanceParameterValue> WithName(const TOptional<FString> Name);
        TSharedPtr<FBalanceParameterValue> WithValue(const TOptional<int64> Value);

        TOptional<FString> GetName() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;


        static TSharedPtr<FBalanceParameterValue> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBalanceParameterValue, ESPMode::ThreadSafe> FBalanceParameterValuePtr;
}