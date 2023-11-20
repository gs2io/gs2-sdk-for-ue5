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

#include "Schedule/Model/Gs2ScheduleEzTrigger.h"

namespace Gs2::UE5::Schedule::Model
{

    TSharedPtr<FEzTrigger> FEzTrigger::WithTriggerId(
        const TOptional<FString> TriggerId
    )
    {
        this->TriggerIdValue = TriggerId;
        return SharedThis(this);
    }

    TSharedPtr<FEzTrigger> FEzTrigger::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzTrigger> FEzTrigger::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzTrigger> FEzTrigger::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzTrigger::GetTriggerId() const
    {
        return TriggerIdValue;
    }
    TOptional<FString> FEzTrigger::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FEzTrigger::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzTrigger::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FEzTrigger::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FEzTrigger::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    Gs2::Schedule::Model::FTriggerPtr FEzTrigger::ToModel() const
    {
        return MakeShared<Gs2::Schedule::Model::FTrigger>()
            ->WithTriggerId(TriggerIdValue)
            ->WithName(NameValue)
            ->WithCreatedAt(CreatedAtValue)
            ->WithExpiresAt(ExpiresAtValue);
    }

    TSharedPtr<FEzTrigger> FEzTrigger::FromModel(const Gs2::Schedule::Model::FTriggerPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzTrigger>()
            ->WithTriggerId(Model->GetTriggerId())
            ->WithName(Model->GetName())
            ->WithCreatedAt(Model->GetCreatedAt())
            ->WithExpiresAt(Model->GetExpiresAt());
    }
}