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
#include "Stamina/Model/Stamina.h"

namespace Gs2::UE5::Stamina::Model
{
	class EZGS2_API FEzStamina final : public TSharedFromThis<FEzStamina>
	{
        TOptional<FString> StaminaNameValue;
        TOptional<int32> ValueValue;
        TOptional<int32> OverflowValueValue;
        TOptional<int32> MaxValueValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<int32> RecoverValueValue;
        TOptional<int64> NextRecoverAtValue;

	public:
        TSharedPtr<FEzStamina> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FEzStamina> WithValue(const TOptional<int32> Value);
        TSharedPtr<FEzStamina> WithOverflowValue(const TOptional<int32> OverflowValue);
        TSharedPtr<FEzStamina> WithMaxValue(const TOptional<int32> MaxValue);
        TSharedPtr<FEzStamina> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FEzStamina> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FEzStamina> WithNextRecoverAt(const TOptional<int64> NextRecoverAt);

        TOptional<FString> GetStaminaName() const;

        TOptional<int32> GetValue() const;
        FString GetValueString() const;

        TOptional<int32> GetOverflowValue() const;
        FString GetOverflowValueString() const;

        TOptional<int32> GetMaxValue() const;
        FString GetMaxValueString() const;

        TOptional<int32> GetRecoverIntervalMinutes() const;
        FString GetRecoverIntervalMinutesString() const;

        TOptional<int32> GetRecoverValue() const;
        FString GetRecoverValueString() const;

        TOptional<int64> GetNextRecoverAt() const;
        FString GetNextRecoverAtString() const;

        Gs2::Stamina::Model::FStaminaPtr ToModel() const;
        static TSharedPtr<FEzStamina> FromModel(Gs2::Stamina::Model::FStaminaPtr Model);
    };
    typedef TSharedPtr<FEzStamina> FEzStaminaPtr;
}