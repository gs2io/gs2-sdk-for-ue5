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

#include "Idle/Model/Gs2IdleEzStatus.h"

namespace Gs2::UE5::Idle::Model
{

    TSharedPtr<FEzStatus> FEzStatus::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithRandomSeed(
        const TOptional<int64> RandomSeed
    )
    {
        this->RandomSeedValue = RandomSeed;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithIdleMinutes(
        const TOptional<int32> IdleMinutes
    )
    {
        this->IdleMinutesValue = IdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithMaximumIdleMinutes(
        const TOptional<int32> MaximumIdleMinutes
    )
    {
        this->MaximumIdleMinutesValue = MaximumIdleMinutes;
        return SharedThis(this);
    }
    TOptional<FString> FEzStatus::GetCategoryName() const
    {
        return CategoryNameValue;
    }
    TOptional<int64> FEzStatus::GetRandomSeed() const
    {
        return RandomSeedValue;
    }

    FString FEzStatus::GetRandomSeedString() const
    {
        if (!RandomSeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue());
    }
    TOptional<int32> FEzStatus::GetIdleMinutes() const
    {
        return IdleMinutesValue;
    }

    FString FEzStatus::GetIdleMinutesString() const
    {
        if (!IdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IdleMinutesValue.GetValue());
    }
    TOptional<int32> FEzStatus::GetMaximumIdleMinutes() const
    {
        return MaximumIdleMinutesValue;
    }

    FString FEzStatus::GetMaximumIdleMinutesString() const
    {
        if (!MaximumIdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumIdleMinutesValue.GetValue());
    }

    Gs2::Idle::Model::FStatusPtr FEzStatus::ToModel() const
    {
        return MakeShared<Gs2::Idle::Model::FStatus>()
            ->WithCategoryName(CategoryNameValue)
            ->WithRandomSeed(RandomSeedValue)
            ->WithIdleMinutes(IdleMinutesValue)
            ->WithMaximumIdleMinutes(MaximumIdleMinutesValue);
    }

    TSharedPtr<FEzStatus> FEzStatus::FromModel(const Gs2::Idle::Model::FStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStatus>()
            ->WithCategoryName(Model->GetCategoryName())
            ->WithRandomSeed(Model->GetRandomSeed())
            ->WithIdleMinutes(Model->GetIdleMinutes())
            ->WithMaximumIdleMinutes(Model->GetMaximumIdleMinutes());
    }
}