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

#include "SeasonRating/Model/SeasonModelMaster.h"

namespace Gs2::SeasonRating::Model
{
    FSeasonModelMaster::FSeasonModelMaster():
        SeasonModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TiersValue(nullptr),
        ExperienceModelIdValue(TOptional<FString>()),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FSeasonModelMaster::FSeasonModelMaster(
        const FSeasonModelMaster& From
    ):
        SeasonModelIdValue(From.SeasonModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        TiersValue(From.TiersValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithSeasonModelId(
        const TOptional<FString> SeasonModelId
    )
    {
        this->SeasonModelIdValue = SeasonModelId;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithTiers(
        const TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> Tiers
    )
    {
        this->TiersValue = Tiers;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FSeasonModelMaster::GetSeasonModelId() const
    {
        return SeasonModelIdValue;
    }
    TOptional<FString> FSeasonModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSeasonModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FSeasonModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> FSeasonModelMaster::GetTiers() const
    {
        return TiersValue;
    }
    TOptional<FString> FSeasonModelMaster::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TOptional<FString> FSeasonModelMaster::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }
    TOptional<int64> FSeasonModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSeasonModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FSeasonModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FSeasonModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FSeasonModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FSeasonModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FSeasonModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):seasonRating:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):seasonRating:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):seasonRating:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonModelMaster::GetSeasonNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):seasonRating:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSeasonModelMaster> FSeasonModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSeasonModelMaster>()
            ->WithSeasonModelId(Data->HasField("seasonModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("seasonModelId", v))
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTiers(Data->HasField("tiers") ? [Data]() -> TSharedPtr<TArray<Model::FTierModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FTierModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("tiers") && Data->HasTypedField<EJson::Array>("tiers"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("tiers"))
                        {
                            v->Add(Model::FTierModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FTierModelPtr>>())
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("experienceModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithChallengePeriodEventId(Data->HasField("challengePeriodEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("challengePeriodEventId", v))
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

    TSharedPtr<FJsonObject> FSeasonModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SeasonModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonModelId", SeasonModelIdValue.GetValue());
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
        if (TiersValue != nullptr && TiersValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TiersValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("tiers", v);
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
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

    FString FSeasonModelMaster::TypeName = "SeasonModelMaster";
}