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
#include "Core/Gs2Object.h"

namespace Gs2::Stamina::Model
{
    class GS2STAMINA_API FStaminaModelMaster final : public FGs2Object, public TSharedFromThis<FStaminaModelMaster>
    {
        TOptional<FString> StaminaModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<int32> RecoverValueValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<bool> IsOverflowValue;
        TOptional<int32> MaxCapacityValue;
        TOptional<FString> MaxStaminaTableNameValue;
        TOptional<FString> RecoverIntervalTableNameValue;
        TOptional<FString> RecoverValueTableNameValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FStaminaModelMaster();
        FStaminaModelMaster(
            const FStaminaModelMaster& From
        );
        virtual ~FStaminaModelMaster() override = default;

        TSharedPtr<FStaminaModelMaster> WithStaminaModelId(const TOptional<FString> StaminaModelId);
        TSharedPtr<FStaminaModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FStaminaModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FStaminaModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FStaminaModelMaster> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FStaminaModelMaster> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FStaminaModelMaster> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FStaminaModelMaster> WithIsOverflow(const TOptional<bool> IsOverflow);
        TSharedPtr<FStaminaModelMaster> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FStaminaModelMaster> WithMaxStaminaTableName(const TOptional<FString> MaxStaminaTableName);
        TSharedPtr<FStaminaModelMaster> WithRecoverIntervalTableName(const TOptional<FString> RecoverIntervalTableName);
        TSharedPtr<FStaminaModelMaster> WithRecoverValueTableName(const TOptional<FString> RecoverValueTableName);
        TSharedPtr<FStaminaModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStaminaModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FStaminaModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetStaminaModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
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
        TOptional<FString> GetMaxStaminaTableName() const;
        TOptional<FString> GetRecoverIntervalTableName() const;
        TOptional<FString> GetRecoverValueTableName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetStaminaNameFromGrn(const FString Grn);

        static TSharedPtr<FStaminaModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStaminaModelMaster, ESPMode::ThreadSafe> FStaminaModelMasterPtr;
}