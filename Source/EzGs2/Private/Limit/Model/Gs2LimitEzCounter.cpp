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

#include "EzGs2/Public/Limit/Model/Gs2LimitEzCounter.h"

namespace Gs2::UE5::Limit::Model
{

    TSharedPtr<FEzCounter> FEzCounter::WithCounterId(
        const TOptional<FString> CounterId
    )
    {
        this->CounterIdValue = CounterId;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounter> FEzCounter::WithLimitName(
        const TOptional<FString> LimitName
    )
    {
        this->LimitNameValue = LimitName;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounter> FEzCounter::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounter> FEzCounter::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounter> FEzCounter::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounter> FEzCounter::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzCounter::GetCounterId() const
    {
        return CounterIdValue;
    }
    TOptional<FString> FEzCounter::GetLimitName() const
    {
        return LimitNameValue;
    }
    TOptional<FString> FEzCounter::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FEzCounter::GetCount() const
    {
        return CountValue;
    }

    FString FEzCounter::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), CountValue.GetValue());
    }
    TOptional<int64> FEzCounter::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzCounter::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FEzCounter::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzCounter::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Limit::Model::FCounterPtr FEzCounter::ToModel() const
    {
        return MakeShared<Gs2::Limit::Model::FCounter>()
            ->WithCounterId(CounterIdValue)
            ->WithLimitName(LimitNameValue)
            ->WithName(NameValue)
            ->WithCount(CountValue)
            ->WithCreatedAt(CreatedAtValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzCounter> FEzCounter::FromModel(const Gs2::Limit::Model::FCounterPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCounter>()
            ->WithCounterId(Model->GetCounterId())
            ->WithLimitName(Model->GetLimitName())
            ->WithName(Model->GetName())
            ->WithCount(Model->GetCount())
            ->WithCreatedAt(Model->GetCreatedAt())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}