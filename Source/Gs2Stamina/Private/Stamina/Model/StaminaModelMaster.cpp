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

#include "Stamina/Model/StaminaModelMaster.h"

namespace Gs2::Stamina::Model
{
    FStaminaModelMaster::FStaminaModelMaster():
        StaminaModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        RecoverIntervalMinutesValue(TOptional<int32>()),
        RecoverValueValue(TOptional<int32>()),
        InitialCapacityValue(TOptional<int32>()),
        IsOverflowValue(TOptional<bool>()),
        MaxCapacityValue(TOptional<int32>()),
        MaxStaminaTableNameValue(TOptional<FString>()),
        RecoverIntervalTableNameValue(TOptional<FString>()),
        RecoverValueTableNameValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FStaminaModelMaster::FStaminaModelMaster(
        const FStaminaModelMaster& From
    ):
        StaminaModelIdValue(From.StaminaModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        RecoverIntervalMinutesValue(From.RecoverIntervalMinutesValue),
        RecoverValueValue(From.RecoverValueValue),
        InitialCapacityValue(From.InitialCapacityValue),
        IsOverflowValue(From.IsOverflowValue),
        MaxCapacityValue(From.MaxCapacityValue),
        MaxStaminaTableNameValue(From.MaxStaminaTableNameValue),
        RecoverIntervalTableNameValue(From.RecoverIntervalTableNameValue),
        RecoverValueTableNameValue(From.RecoverValueTableNameValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithStaminaModelId(
        const TOptional<FString> StaminaModelId
    )
    {
        this->StaminaModelIdValue = StaminaModelId;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithIsOverflow(
        const TOptional<bool> IsOverflow
    )
    {
        this->IsOverflowValue = IsOverflow;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithMaxStaminaTableName(
        const TOptional<FString> MaxStaminaTableName
    )
    {
        this->MaxStaminaTableNameValue = MaxStaminaTableName;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithRecoverIntervalTableName(
        const TOptional<FString> RecoverIntervalTableName
    )
    {
        this->RecoverIntervalTableNameValue = RecoverIntervalTableName;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithRecoverValueTableName(
        const TOptional<FString> RecoverValueTableName
    )
    {
        this->RecoverValueTableNameValue = RecoverValueTableName;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FStaminaModelMaster::GetStaminaModelId() const
    {
        return StaminaModelIdValue;
    }
    TOptional<FString> FStaminaModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FStaminaModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FStaminaModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<int32> FStaminaModelMaster::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FStaminaModelMaster::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FStaminaModelMaster::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FStaminaModelMaster::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }
    TOptional<int32> FStaminaModelMaster::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FStaminaModelMaster::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }
    TOptional<bool> FStaminaModelMaster::GetIsOverflow() const
    {
        return IsOverflowValue;
    }

    FString FStaminaModelMaster::GetIsOverflowString() const
    {
        if (!IsOverflowValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsOverflowValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FStaminaModelMaster::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FStaminaModelMaster::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }
    TOptional<FString> FStaminaModelMaster::GetMaxStaminaTableName() const
    {
        return MaxStaminaTableNameValue;
    }
    TOptional<FString> FStaminaModelMaster::GetRecoverIntervalTableName() const
    {
        return RecoverIntervalTableNameValue;
    }
    TOptional<FString> FStaminaModelMaster::GetRecoverValueTableName() const
    {
        return RecoverValueTableNameValue;
    }
    TOptional<int64> FStaminaModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStaminaModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FStaminaModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FStaminaModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FStaminaModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FStaminaModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FStaminaModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModelMaster::GetStaminaNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStaminaModelMaster> FStaminaModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStaminaModelMaster>()
            ->WithStaminaModelId(Data->HasField("staminaModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("staminaModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRecoverIntervalMinutes(Data->HasField("recoverIntervalMinutes") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("recoverIntervalMinutes", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRecoverValue(Data->HasField("recoverValue") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("recoverValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithInitialCapacity(Data->HasField("initialCapacity") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("initialCapacity", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithIsOverflow(Data->HasField("isOverflow") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("isOverflow", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithMaxCapacity(Data->HasField("maxCapacity") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maxCapacity", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxStaminaTableName(Data->HasField("maxStaminaTableName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("maxStaminaTableName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRecoverIntervalTableName(Data->HasField("recoverIntervalTableName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("recoverIntervalTableName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRecoverValueTableName(Data->HasField("recoverValueTableName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("recoverValueTableName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FStaminaModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StaminaModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaModelId", StaminaModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (RecoverIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverIntervalMinutes", RecoverIntervalMinutesValue.GetValue());
        }
        if (RecoverValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverValue", RecoverValueValue.GetValue());
        }
        if (InitialCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("initialCapacity", InitialCapacityValue.GetValue());
        }
        if (IsOverflowValue.IsSet())
        {
            JsonRootObject->SetBoolField("isOverflow", IsOverflowValue.GetValue());
        }
        if (MaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxCapacity", MaxCapacityValue.GetValue());
        }
        if (MaxStaminaTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("maxStaminaTableName", MaxStaminaTableNameValue.GetValue());
        }
        if (RecoverIntervalTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("recoverIntervalTableName", RecoverIntervalTableNameValue.GetValue());
        }
        if (RecoverValueTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("recoverValueTableName", RecoverValueTableNameValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FStaminaModelMaster::TypeName = "StaminaModelMaster";
}