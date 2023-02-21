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

#include "Formation/Model/MoldModelMaster.h"

namespace Gs2::Formation::Model
{
    FMoldModelMaster::FMoldModelMaster():
        MoldModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        InitialMaxCapacityValue(TOptional<int32>()),
        MaxCapacityValue(TOptional<int32>()),
        FormModelNameValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FMoldModelMaster::FMoldModelMaster(
        const FMoldModelMaster& From
    ):
        MoldModelIdValue(From.MoldModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        InitialMaxCapacityValue(From.InitialMaxCapacityValue),
        MaxCapacityValue(From.MaxCapacityValue),
        FormModelNameValue(From.FormModelNameValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithMoldModelId(
        const TOptional<FString> MoldModelId
    )
    {
        this->MoldModelIdValue = MoldModelId;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithInitialMaxCapacity(
        const TOptional<int32> InitialMaxCapacity
    )
    {
        this->InitialMaxCapacityValue = InitialMaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithFormModelName(
        const TOptional<FString> FormModelName
    )
    {
        this->FormModelNameValue = FormModelName;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FMoldModelMaster::GetMoldModelId() const
    {
        return MoldModelIdValue;
    }
    TOptional<FString> FMoldModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMoldModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FMoldModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FMoldModelMaster::GetInitialMaxCapacity() const
    {
        return InitialMaxCapacityValue;
    }

    FString FMoldModelMaster::GetInitialMaxCapacityString() const
    {
        if (!InitialMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), InitialMaxCapacityValue.GetValue());
    }
    TOptional<int32> FMoldModelMaster::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FMoldModelMaster::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MaxCapacityValue.GetValue());
    }
    TOptional<FString> FMoldModelMaster::GetFormModelName() const
    {
        return FormModelNameValue;
    }
    TOptional<int64> FMoldModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FMoldModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FMoldModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FMoldModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FMoldModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMoldModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMoldModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMoldModelMaster::GetMoldNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FMoldModelMaster> FMoldModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMoldModelMaster>()
            ->WithMoldModelId(Data->HasField("moldModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("moldModelId", v))
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
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
            ->WithInitialMaxCapacity(Data->HasField("initialMaxCapacity") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("initialMaxCapacity", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxCapacity(Data->HasField("maxCapacity") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maxCapacity", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithFormModelName(Data->HasField("formModelName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("formModelName", v))
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FMoldModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MoldModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("moldModelId", MoldModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (InitialMaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("initialMaxCapacity", InitialMaxCapacityValue.GetValue());
        }
        if (MaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxCapacity", MaxCapacityValue.GetValue());
        }
        if (FormModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("formModelName", FormModelNameValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FMoldModelMaster::TypeName = "MoldModelMaster";
}