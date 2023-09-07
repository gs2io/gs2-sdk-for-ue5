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

#include "Formation/Model/MoldModel.h"

namespace Gs2::Formation::Model
{
    FMoldModel::FMoldModel():
        MoldModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        InitialMaxCapacityValue(TOptional<int32>()),
        MaxCapacityValue(TOptional<int32>()),
        FormModelValue(nullptr)
    {
    }

    FMoldModel::FMoldModel(
        const FMoldModel& From
    ):
        MoldModelIdValue(From.MoldModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        InitialMaxCapacityValue(From.InitialMaxCapacityValue),
        MaxCapacityValue(From.MaxCapacityValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FMoldModel> FMoldModel::WithMoldModelId(
        const TOptional<FString> MoldModelId
    )
    {
        this->MoldModelIdValue = MoldModelId;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModel> FMoldModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModel> FMoldModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModel> FMoldModel::WithInitialMaxCapacity(
        const TOptional<int32> InitialMaxCapacity
    )
    {
        this->InitialMaxCapacityValue = InitialMaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModel> FMoldModel::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FMoldModel> FMoldModel::WithFormModel(
        const TSharedPtr<FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }
    TOptional<FString> FMoldModel::GetMoldModelId() const
    {
        return MoldModelIdValue;
    }
    TOptional<FString> FMoldModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMoldModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FMoldModel::GetInitialMaxCapacity() const
    {
        return InitialMaxCapacityValue;
    }

    FString FMoldModel::GetInitialMaxCapacityString() const
    {
        if (!InitialMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialMaxCapacityValue.GetValue());
    }
    TOptional<int32> FMoldModel::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FMoldModel::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }
    TSharedPtr<FFormModel> FMoldModel::GetFormModel() const
    {
        return FormModelValue;
    }

    TOptional<FString> FMoldModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMoldModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMoldModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMoldModel::GetMoldModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):formation:(?<namespaceName>.+):model:mold:(?<moldModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FMoldModel> FMoldModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMoldModel>()
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
            ->WithFormModel(Data->HasField("formModel") ? [Data]() -> Model::FFormModelPtr
                {
                    if (Data->HasTypedField<EJson::Null>("formModel"))
                    {
                        return nullptr;
                    }
                    return Model::FFormModel::FromJson(Data->GetObjectField("formModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FMoldModel::ToJson() const
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
        if (FormModelValue != nullptr && FormModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("formModel", FormModelValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FMoldModel::TypeName = "MoldModel";
}