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

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FScopedValue final : public FGs2Object, public TSharedFromThis<FScopedValue>
    {
        TOptional<FString> ScopeTypeValue;
        TOptional<FString> ResetTypeValue;
        TOptional<FString> ConditionNameValue;
        TOptional<int64> ValueValue;
        TOptional<int64> NextResetAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FScopedValue();
        FScopedValue(
            const FScopedValue& From
        );
        virtual ~FScopedValue() override = default;

        TSharedPtr<FScopedValue> WithScopeType(const TOptional<FString> ScopeType);
        TSharedPtr<FScopedValue> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FScopedValue> WithConditionName(const TOptional<FString> ConditionName);
        TSharedPtr<FScopedValue> WithValue(const TOptional<int64> Value);
        TSharedPtr<FScopedValue> WithNextResetAt(const TOptional<int64> NextResetAt);
        TSharedPtr<FScopedValue> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetScopeType() const;
        TOptional<FString> GetResetType() const;
        TOptional<FString> GetConditionName() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;
        TOptional<int64> GetNextResetAt() const;
        FString GetNextResetAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;


        static TSharedPtr<FScopedValue> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScopedValue, ESPMode::ThreadSafe> FScopedValuePtr;
}