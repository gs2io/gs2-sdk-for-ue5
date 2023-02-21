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
#include "Stamina/Model/StaminaModel.h"
#include "Gs2StaminaEzMaxStaminaTable.h"
#include "Gs2StaminaEzRecoverIntervalTable.h"
#include "Gs2StaminaEzRecoverValueTable.h"

namespace Gs2::UE5::Stamina::Model
{
	class EZGS2_API FEzStaminaModel final : public TSharedFromThis<FEzStaminaModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<int32> RecoverValueValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<bool> IsOverflowValue;
        TOptional<int32> MaxCapacityValue;
        TSharedPtr<Gs2::UE5::Stamina::Model::FEzMaxStaminaTable> MaxStaminaTableValue;
        TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverIntervalTable> RecoverIntervalTableValue;
        TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverValueTable> RecoverValueTableValue;

	public:
        TSharedPtr<FEzStaminaModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzStaminaModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzStaminaModel> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FEzStaminaModel> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FEzStaminaModel> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FEzStaminaModel> WithIsOverflow(const TOptional<bool> IsOverflow);
        TSharedPtr<FEzStaminaModel> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FEzStaminaModel> WithMaxStaminaTable(const TSharedPtr<Gs2::UE5::Stamina::Model::FEzMaxStaminaTable> MaxStaminaTable);
        TSharedPtr<FEzStaminaModel> WithRecoverIntervalTable(const TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverIntervalTable> RecoverIntervalTable);
        TSharedPtr<FEzStaminaModel> WithRecoverValueTable(const TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverValueTable> RecoverValueTable);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int32> GetRecoverIntervalMinutes() const;
        FString GetRecoverIntervalMinutesString() const;

        TOptional<int32> GetRecoverValue() const;
        FString GetRecoverValueString() const;

        TOptional<int32> GetInitialCapacity() const;
        FString GetInitialCapacityString() const;

        TOptional<bool> GetIsOverflow() const;
        FString GetIsOverflowString() const;

        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;

        TSharedPtr<Gs2::UE5::Stamina::Model::FEzMaxStaminaTable> GetMaxStaminaTable() const;

        TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverIntervalTable> GetRecoverIntervalTable() const;

        TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverValueTable> GetRecoverValueTable() const;

        Gs2::Stamina::Model::FStaminaModelPtr ToModel() const;
        static TSharedPtr<FEzStaminaModel> FromModel(Gs2::Stamina::Model::FStaminaModelPtr Model);
    };
    typedef TSharedPtr<FEzStaminaModel> FEzStaminaModelPtr;
}