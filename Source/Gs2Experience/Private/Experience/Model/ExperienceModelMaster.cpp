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

#include "Experience/Model/ExperienceModelMaster.h"

namespace Gs2::Experience::Model
{
    FExperienceModelMaster::FExperienceModelMaster():
        ExperienceModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultExperienceValue(TOptional<int64>()),
        DefaultRankCapValue(TOptional<int64>()),
        MaxRankCapValue(TOptional<int64>()),
        RankThresholdNameValue(TOptional<FString>()),
        AcquireActionRatesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FExperienceModelMaster::FExperienceModelMaster(
        const FExperienceModelMaster& From
    ):
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        DefaultExperienceValue(From.DefaultExperienceValue),
        DefaultRankCapValue(From.DefaultRankCapValue),
        MaxRankCapValue(From.MaxRankCapValue),
        RankThresholdNameValue(From.RankThresholdNameValue),
        AcquireActionRatesValue(From.AcquireActionRatesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithDefaultExperience(
        const TOptional<int64> DefaultExperience
    )
    {
        this->DefaultExperienceValue = DefaultExperience;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithDefaultRankCap(
        const TOptional<int64> DefaultRankCap
    )
    {
        this->DefaultRankCapValue = DefaultRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithMaxRankCap(
        const TOptional<int64> MaxRankCap
    )
    {
        this->MaxRankCapValue = MaxRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithRankThresholdName(
        const TOptional<FString> RankThresholdName
    )
    {
        this->RankThresholdNameValue = RankThresholdName;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithAcquireActionRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates
    )
    {
        this->AcquireActionRatesValue = AcquireActionRates;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FExperienceModelMaster::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TOptional<FString> FExperienceModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FExperienceModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FExperienceModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FExperienceModelMaster::GetDefaultExperience() const
    {
        return DefaultExperienceValue;
    }

    FString FExperienceModelMaster::GetDefaultExperienceString() const
    {
        if (!DefaultExperienceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetDefaultRankCap() const
    {
        return DefaultRankCapValue;
    }

    FString FExperienceModelMaster::GetDefaultRankCapString() const
    {
        if (!DefaultRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetMaxRankCap() const
    {
        return MaxRankCapValue;
    }

    FString FExperienceModelMaster::GetMaxRankCapString() const
    {
        if (!MaxRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue());
    }
    TOptional<FString> FExperienceModelMaster::GetRankThresholdName() const
    {
        return RankThresholdNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> FExperienceModelMaster::GetAcquireActionRates() const
    {
        return AcquireActionRatesValue;
    }
    TOptional<int64> FExperienceModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FExperienceModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FExperienceModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FExperienceModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FExperienceModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModelMaster::GetExperienceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FExperienceModelMaster>()
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("experienceModelId", v))
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
            ->WithDefaultExperience(Data->HasField("defaultExperience") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("defaultExperience", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithDefaultRankCap(Data->HasField("defaultRankCap") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("defaultRankCap", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMaxRankCap(Data->HasField("maxRankCap") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("maxRankCap", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRankThresholdName(Data->HasField("rankThresholdName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rankThresholdName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
                 }() : MakeShared<TArray<Model::FAcquireActionRatePtr>>())
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

    TSharedPtr<FJsonObject> FExperienceModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
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
        if (DefaultExperienceValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultExperience", FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue()));
        }
        if (DefaultRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultRankCap", FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue()));
        }
        if (MaxRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField("maxRankCap", FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue()));
        }
        if (RankThresholdNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rankThresholdName", RankThresholdNameValue.GetValue());
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

    FString FExperienceModelMaster::TypeName = "ExperienceModelMaster";
}