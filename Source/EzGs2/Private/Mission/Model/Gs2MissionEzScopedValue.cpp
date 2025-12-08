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

#include "Mission/Model/Gs2MissionEzScopedValue.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzScopedValue> FEzScopedValue::WithScopeType(
        const TOptional<FString> ScopeType
    )
    {
        this->ScopeTypeValue = ScopeType;
        return SharedThis(this);
    }

    TSharedPtr<FEzScopedValue> FEzScopedValue::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FEzScopedValue> FEzScopedValue::WithConditionName(
        const TOptional<FString> ConditionName
    )
    {
        this->ConditionNameValue = ConditionName;
        return SharedThis(this);
    }

    TSharedPtr<FEzScopedValue> FEzScopedValue::WithValue(
        const TOptional<int64> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzScopedValue::GetScopeType() const
    {
        return ScopeTypeValue;
    }
    TOptional<FString> FEzScopedValue::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<FString> FEzScopedValue::GetConditionName() const
    {
        return ConditionNameValue;
    }
    TOptional<int64> FEzScopedValue::GetValue() const
    {
        return ValueValue;
    }

    FString FEzScopedValue::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ValueValue.GetValue());
    }

    Gs2::Mission::Model::FScopedValuePtr FEzScopedValue::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FScopedValue>()
            ->WithScopeType(ScopeTypeValue)
            ->WithResetType(ResetTypeValue)
            ->WithConditionName(ConditionNameValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzScopedValue> FEzScopedValue::FromModel(const Gs2::Mission::Model::FScopedValuePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzScopedValue>()
            ->WithScopeType(Model->GetScopeType())
            ->WithResetType(Model->GetResetType())
            ->WithConditionName(Model->GetConditionName())
            ->WithValue(Model->GetValue());
    }
}