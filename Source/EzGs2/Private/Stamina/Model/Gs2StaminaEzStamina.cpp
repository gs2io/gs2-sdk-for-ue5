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

#include "EzGs2/Public/Stamina/Model/Gs2StaminaEzStamina.h"

namespace Gs2::UE5::Stamina::Model
{

    TSharedPtr<FEzStamina> FEzStamina::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FEzStamina> FEzStamina::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FEzStamina> FEzStamina::WithOverflowValue(
        const TOptional<int32> OverflowValue
    )
    {
        this->OverflowValueValue = OverflowValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzStamina> FEzStamina::WithMaxValue(
        const TOptional<int32> MaxValue
    )
    {
        this->MaxValueValue = MaxValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzStamina> FEzStamina::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FEzStamina> FEzStamina::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzStamina> FEzStamina::WithNextRecoverAt(
        const TOptional<int64> NextRecoverAt
    )
    {
        this->NextRecoverAtValue = NextRecoverAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzStamina::GetStaminaName() const
    {
        return StaminaNameValue;
    }
    TOptional<int32> FEzStamina::GetValue() const
    {
        return ValueValue;
    }

    FString FEzStamina::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), ValueValue.GetValue());
    }
    TOptional<int32> FEzStamina::GetOverflowValue() const
    {
        return OverflowValueValue;
    }

    FString FEzStamina::GetOverflowValueString() const
    {
        if (!OverflowValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), OverflowValueValue.GetValue());
    }
    TOptional<int32> FEzStamina::GetMaxValue() const
    {
        return MaxValueValue;
    }

    FString FEzStamina::GetMaxValueString() const
    {
        if (!MaxValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MaxValueValue.GetValue());
    }
    TOptional<int32> FEzStamina::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FEzStamina::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), RecoverIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FEzStamina::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FEzStamina::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), RecoverValueValue.GetValue());
    }
    TOptional<int64> FEzStamina::GetNextRecoverAt() const
    {
        return NextRecoverAtValue;
    }

    FString FEzStamina::GetNextRecoverAtString() const
    {
        if (!NextRecoverAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRecoverAtValue.GetValue());
    }

    Gs2::Stamina::Model::FStaminaPtr FEzStamina::ToModel() const
    {
        return MakeShared<Gs2::Stamina::Model::FStamina>()
            ->WithStaminaName(StaminaNameValue)
            ->WithValue(ValueValue)
            ->WithOverflowValue(OverflowValueValue)
            ->WithMaxValue(MaxValueValue)
            ->WithRecoverIntervalMinutes(RecoverIntervalMinutesValue)
            ->WithRecoverValue(RecoverValueValue)
            ->WithNextRecoverAt(NextRecoverAtValue);
    }

    TSharedPtr<FEzStamina> FEzStamina::FromModel(const Gs2::Stamina::Model::FStaminaPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStamina>()
            ->WithStaminaName(Model->GetStaminaName())
            ->WithValue(Model->GetValue())
            ->WithOverflowValue(Model->GetOverflowValue())
            ->WithMaxValue(Model->GetMaxValue())
            ->WithRecoverIntervalMinutes(Model->GetRecoverIntervalMinutes())
            ->WithRecoverValue(Model->GetRecoverValue())
            ->WithNextRecoverAt(Model->GetNextRecoverAt());
    }
}