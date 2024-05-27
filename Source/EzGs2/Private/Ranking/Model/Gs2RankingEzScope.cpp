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

#include "Ranking/Model/Gs2RankingEzScope.h"

namespace Gs2::UE5::Ranking::Model
{

    TSharedPtr<FEzScope> FEzScope::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzScope> FEzScope::WithTargetDays(
        const TOptional<int64> TargetDays
    )
    {
        this->TargetDaysValue = TargetDays;
        return SharedThis(this);
    }
    TOptional<FString> FEzScope::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FEzScope::GetTargetDays() const
    {
        return TargetDaysValue;
    }

    FString FEzScope::GetTargetDaysString() const
    {
        if (!TargetDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TargetDaysValue.GetValue());
    }

    Gs2::Ranking::Model::FScopePtr FEzScope::ToModel() const
    {
        return MakeShared<Gs2::Ranking::Model::FScope>()
            ->WithName(NameValue)
            ->WithTargetDays(TargetDaysValue);
    }

    TSharedPtr<FEzScope> FEzScope::FromModel(const Gs2::Ranking::Model::FScopePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzScope>()
            ->WithName(Model->GetName())
            ->WithTargetDays(Model->GetTargetDays());
    }
}