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

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FScopeValue final : public FGs2Object, public TSharedFromThis<FScopeValue>
    {
        TOptional<FString> KeyValue;
        TOptional<FString> ValueValue;

    public:
        FScopeValue();
        FScopeValue(
            const FScopeValue& From
        );
        virtual ~FScopeValue() override = default;

        TSharedPtr<FScopeValue> WithKey(const TOptional<FString> Key);
        TSharedPtr<FScopeValue> WithValue(const TOptional<FString> Value);

        TOptional<FString> GetKey() const;
        TOptional<FString> GetValue() const;


        static TSharedPtr<FScopeValue> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScopeValue, ESPMode::ThreadSafe> FScopeValuePtr;
}