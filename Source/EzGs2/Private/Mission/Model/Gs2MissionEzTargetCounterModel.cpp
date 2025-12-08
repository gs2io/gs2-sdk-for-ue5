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

#include "Mission/Model/Gs2MissionEzTargetCounterModel.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzTargetCounterModel> FEzTargetCounterModel::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FEzTargetCounterModel> FEzTargetCounterModel::WithScopeType(
        const TOptional<FString> ScopeType
    )
    {
        this->ScopeTypeValue = ScopeType;
        return SharedThis(this);
    }

    TSharedPtr<FEzTargetCounterModel> FEzTargetCounterModel::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FEzTargetCounterModel> FEzTargetCounterModel::WithConditionName(
        const TOptional<FString> ConditionName
    )
    {
        this->ConditionNameValue = ConditionName;
        return SharedThis(this);
    }

    TSharedPtr<FEzTargetCounterModel> FEzTargetCounterModel::WithValue(
        const TOptional<int64> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzTargetCounterModel::GetCounterName() const
    {
        return CounterNameValue;
    }
    TOptional<FString> FEzTargetCounterModel::GetScopeType() const
    {
        return ScopeTypeValue;
    }
    TOptional<FString> FEzTargetCounterModel::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<FString> FEzTargetCounterModel::GetConditionName() const
    {
        return ConditionNameValue;
    }
    TOptional<int64> FEzTargetCounterModel::GetValue() const
    {
        return ValueValue;
    }

    FString FEzTargetCounterModel::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ValueValue.GetValue());
    }

    Gs2::Mission::Model::FTargetCounterModelPtr FEzTargetCounterModel::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FTargetCounterModel>()
            ->WithCounterName(CounterNameValue)
            ->WithScopeType(ScopeTypeValue)
            ->WithResetType(ResetTypeValue)
            ->WithConditionName(ConditionNameValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzTargetCounterModel> FEzTargetCounterModel::FromModel(const Gs2::Mission::Model::FTargetCounterModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzTargetCounterModel>()
            ->WithCounterName(Model->GetCounterName())
            ->WithScopeType(Model->GetScopeType())
            ->WithResetType(Model->GetResetType())
            ->WithConditionName(Model->GetConditionName())
            ->WithValue(Model->GetValue());
    }
}