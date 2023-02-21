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
#include "MaxStaminaTable.h"
#include "RecoverIntervalTable.h"
#include "RecoverValueTable.h"

namespace Gs2::Stamina::Model
{
    class GS2STAMINA_API FStaminaModel final : public TSharedFromThis<FStaminaModel>
    {
        TOptional<FString> StaminaModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<int32> RecoverValueValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<bool> IsOverflowValue;
        TOptional<int32> MaxCapacityValue;
        TSharedPtr<FMaxStaminaTable> MaxStaminaTableValue;
        TSharedPtr<FRecoverIntervalTable> RecoverIntervalTableValue;
        TSharedPtr<FRecoverValueTable> RecoverValueTableValue;

    public:
        FStaminaModel();
        FStaminaModel(
            const FStaminaModel& From
        );
        ~FStaminaModel() = default;

        TSharedPtr<FStaminaModel> WithStaminaModelId(const TOptional<FString> StaminaModelId);
        TSharedPtr<FStaminaModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FStaminaModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FStaminaModel> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FStaminaModel> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FStaminaModel> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FStaminaModel> WithIsOverflow(const TOptional<bool> IsOverflow);
        TSharedPtr<FStaminaModel> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FStaminaModel> WithMaxStaminaTable(const TSharedPtr<FMaxStaminaTable> MaxStaminaTable);
        TSharedPtr<FStaminaModel> WithRecoverIntervalTable(const TSharedPtr<FRecoverIntervalTable> RecoverIntervalTable);
        TSharedPtr<FStaminaModel> WithRecoverValueTable(const TSharedPtr<FRecoverValueTable> RecoverValueTable);

        TOptional<FString> GetStaminaModelId() const;
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
        TSharedPtr<FMaxStaminaTable> GetMaxStaminaTable() const;
        TSharedPtr<FRecoverIntervalTable> GetRecoverIntervalTable() const;
        TSharedPtr<FRecoverValueTable> GetRecoverValueTable() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetStaminaNameFromGrn(const FString Grn);

        static TSharedPtr<FStaminaModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStaminaModel, ESPMode::ThreadSafe> FStaminaModelPtr;
}