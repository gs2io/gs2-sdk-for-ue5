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

#include "Grade/Model/GradeModel.h"

namespace Gs2::Grade::Model
{
    FGradeModel::FGradeModel():
        GradeModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultGradesValue(nullptr),
        ExperienceModelIdValue(TOptional<FString>()),
        GradeEntriesValue(nullptr),
        AcquireActionRatesValue(nullptr)
    {
    }

    FGradeModel::FGradeModel(
        const FGradeModel& From
    ):
        GradeModelIdValue(From.GradeModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DefaultGradesValue(From.DefaultGradesValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        GradeEntriesValue(From.GradeEntriesValue),
        AcquireActionRatesValue(From.AcquireActionRatesValue)
    {
    }

    TSharedPtr<FGradeModel> FGradeModel::WithGradeModelId(
        const TOptional<FString> GradeModelId
    )
    {
        this->GradeModelIdValue = GradeModelId;
        return SharedThis(this);
    }

    TSharedPtr<FGradeModel> FGradeModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGradeModel> FGradeModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGradeModel> FGradeModel::WithDefaultGrades(
        const TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> DefaultGrades
    )
    {
        this->DefaultGradesValue = DefaultGrades;
        return SharedThis(this);
    }

    TSharedPtr<FGradeModel> FGradeModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FGradeModel> FGradeModel::WithGradeEntries(
        const TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> GradeEntries
    )
    {
        this->GradeEntriesValue = GradeEntries;
        return SharedThis(this);
    }

    TSharedPtr<FGradeModel> FGradeModel::WithAcquireActionRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates
    )
    {
        this->AcquireActionRatesValue = AcquireActionRates;
        return SharedThis(this);
    }
    TOptional<FString> FGradeModel::GetGradeModelId() const
    {
        return GradeModelIdValue;
    }
    TOptional<FString> FGradeModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FGradeModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FDefaultGradeModel>>> FGradeModel::GetDefaultGrades() const
    {
        return DefaultGradesValue;
    }
    TOptional<FString> FGradeModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FGradeEntryModel>>> FGradeModel::GetGradeEntries() const
    {
        return GradeEntriesValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> FGradeModel::GetAcquireActionRates() const
    {
        return AcquireActionRatesValue;
    }

    TOptional<FString> FGradeModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):grade:(?<namespaceName>.+):model:(?<gradeName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGradeModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):grade:(?<namespaceName>.+):model:(?<gradeName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGradeModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):grade:(?<namespaceName>.+):model:(?<gradeName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGradeModel::GetGradeNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):grade:(?<namespaceName>.+):model:(?<gradeName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGradeModel> FGradeModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGradeModel>()
            ->WithGradeModelId(Data->HasField("gradeModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("gradeModelId", v))
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
            ->WithDefaultGrades(Data->HasField("defaultGrades") ? [Data]() -> TSharedPtr<TArray<Model::FDefaultGradeModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FDefaultGradeModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("defaultGrades") && Data->HasTypedField<EJson::Array>("defaultGrades"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("defaultGrades"))
                        {
                            v->Add(Model::FDefaultGradeModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FDefaultGradeModelPtr>>())
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("experienceModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGradeEntries(Data->HasField("gradeEntries") ? [Data]() -> TSharedPtr<TArray<Model::FGradeEntryModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FGradeEntryModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("gradeEntries") && Data->HasTypedField<EJson::Array>("gradeEntries"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("gradeEntries"))
                        {
                            v->Add(Model::FGradeEntryModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FGradeEntryModelPtr>>())
            ->WithAcquireActionRates(Data->HasField("acquireActionRates") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionRatePtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionRatePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireActionRates") && Data->HasTypedField<EJson::Array>("acquireActionRates"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireActionRates"))
                        {
                            v->Add(Model::FAcquireActionRate::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionRatePtr>>());
    }

    TSharedPtr<FJsonObject> FGradeModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GradeModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeModelId", GradeModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DefaultGradesValue != nullptr && DefaultGradesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DefaultGradesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("defaultGrades", v);
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (GradeEntriesValue != nullptr && GradeEntriesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *GradeEntriesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("gradeEntries", v);
        }
        if (AcquireActionRatesValue != nullptr && AcquireActionRatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionRatesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActionRates", v);
        }
        return JsonRootObject;
    }

    FString FGradeModel::TypeName = "GradeModel";
}