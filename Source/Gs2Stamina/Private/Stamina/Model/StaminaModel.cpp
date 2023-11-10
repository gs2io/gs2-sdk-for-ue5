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

#include "Stamina/Model/StaminaModel.h"

namespace Gs2::Stamina::Model
{
    FStaminaModel::FStaminaModel():
        StaminaModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        RecoverIntervalMinutesValue(TOptional<int32>()),
        RecoverValueValue(TOptional<int32>()),
        InitialCapacityValue(TOptional<int32>()),
        IsOverflowValue(TOptional<bool>()),
        MaxCapacityValue(TOptional<int32>()),
        MaxStaminaTableValue(nullptr),
        RecoverIntervalTableValue(nullptr),
        RecoverValueTableValue(nullptr)
    {
    }

    FStaminaModel::FStaminaModel(
        const FStaminaModel& From
    ):
        StaminaModelIdValue(From.StaminaModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        RecoverIntervalMinutesValue(From.RecoverIntervalMinutesValue),
        RecoverValueValue(From.RecoverValueValue),
        InitialCapacityValue(From.InitialCapacityValue),
        IsOverflowValue(From.IsOverflowValue),
        MaxCapacityValue(From.MaxCapacityValue),
        MaxStaminaTableValue(From.MaxStaminaTableValue),
        RecoverIntervalTableValue(From.RecoverIntervalTableValue),
        RecoverValueTableValue(From.RecoverValueTableValue)
    {
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithStaminaModelId(
        const TOptional<FString> StaminaModelId
    )
    {
        this->StaminaModelIdValue = StaminaModelId;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithIsOverflow(
        const TOptional<bool> IsOverflow
    )
    {
        this->IsOverflowValue = IsOverflow;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithMaxStaminaTable(
        const TSharedPtr<FMaxStaminaTable> MaxStaminaTable
    )
    {
        this->MaxStaminaTableValue = MaxStaminaTable;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverIntervalTable(
        const TSharedPtr<FRecoverIntervalTable> RecoverIntervalTable
    )
    {
        this->RecoverIntervalTableValue = RecoverIntervalTable;
        return SharedThis(this);
    }

    TSharedPtr<FStaminaModel> FStaminaModel::WithRecoverValueTable(
        const TSharedPtr<FRecoverValueTable> RecoverValueTable
    )
    {
        this->RecoverValueTableValue = RecoverValueTable;
        return SharedThis(this);
    }
    TOptional<FString> FStaminaModel::GetStaminaModelId() const
    {
        return StaminaModelIdValue;
    }
    TOptional<FString> FStaminaModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FStaminaModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FStaminaModel::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FStaminaModel::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FStaminaModel::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FStaminaModel::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }
    TOptional<int32> FStaminaModel::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FStaminaModel::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }
    TOptional<bool> FStaminaModel::GetIsOverflow() const
    {
        return IsOverflowValue;
    }

    FString FStaminaModel::GetIsOverflowString() const
    {
        if (!IsOverflowValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsOverflowValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FStaminaModel::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FStaminaModel::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }
    TSharedPtr<FMaxStaminaTable> FStaminaModel::GetMaxStaminaTable() const
    {
        return MaxStaminaTableValue;
    }
    TSharedPtr<FRecoverIntervalTable> FStaminaModel::GetRecoverIntervalTable() const
    {
        return RecoverIntervalTableValue;
    }
    TSharedPtr<FRecoverValueTable> FStaminaModel::GetRecoverValueTable() const
    {
        return RecoverValueTableValue;
    }

    TOptional<FString> FStaminaModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStaminaModel::GetStaminaNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):model:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStaminaModel> FStaminaModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStaminaModel>()
            ->WithStaminaModelId(Data->HasField("staminaModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("staminaModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("metadata", v))
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
            ->WithMaxStaminaTable(Data->HasField("maxStaminaTable") ? [Data]() -> Model::FMaxStaminaTablePtr
                {
                    if (Data->HasTypedField<EJson::Null>("maxStaminaTable"))
                    {
                        return nullptr;
                    }
                    return Model::FMaxStaminaTable::FromJson(Data->GetObjectField("maxStaminaTable"));
                 }() : nullptr)
            ->WithRecoverIntervalTable(Data->HasField("recoverIntervalTable") ? [Data]() -> Model::FRecoverIntervalTablePtr
                {
                    if (Data->HasTypedField<EJson::Null>("recoverIntervalTable"))
                    {
                        return nullptr;
                    }
                    return Model::FRecoverIntervalTable::FromJson(Data->GetObjectField("recoverIntervalTable"));
                 }() : nullptr)
            ->WithRecoverValueTable(Data->HasField("recoverValueTable") ? [Data]() -> Model::FRecoverValueTablePtr
                {
                    if (Data->HasTypedField<EJson::Null>("recoverValueTable"))
                    {
                        return nullptr;
                    }
                    return Model::FRecoverValueTable::FromJson(Data->GetObjectField("recoverValueTable"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FStaminaModel::ToJson() const
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
        if (MaxStaminaTableValue != nullptr && MaxStaminaTableValue.IsValid())
        {
            JsonRootObject->SetObjectField("maxStaminaTable", MaxStaminaTableValue->ToJson());
        }
        if (RecoverIntervalTableValue != nullptr && RecoverIntervalTableValue.IsValid())
        {
            JsonRootObject->SetObjectField("recoverIntervalTable", RecoverIntervalTableValue->ToJson());
        }
        if (RecoverValueTableValue != nullptr && RecoverValueTableValue.IsValid())
        {
            JsonRootObject->SetObjectField("recoverValueTable", RecoverValueTableValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FStaminaModel::TypeName = "StaminaModel";
}