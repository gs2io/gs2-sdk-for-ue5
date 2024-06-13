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

#include "Matchmaking/Model/SeasonGathering.h"

namespace Gs2::Matchmaking::Model
{
    FSeasonGathering::FSeasonGathering():
        SeasonGatheringIdValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        TierValue(TOptional<int64>()),
        NameValue(TOptional<FString>()),
        ParticipantsValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FSeasonGathering::FSeasonGathering(
        const FSeasonGathering& From
    ):
        SeasonGatheringIdValue(From.SeasonGatheringIdValue),
        SeasonNameValue(From.SeasonNameValue),
        SeasonValue(From.SeasonValue),
        TierValue(From.TierValue),
        NameValue(From.NameValue),
        ParticipantsValue(From.ParticipantsValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithSeasonGatheringId(
        const TOptional<FString> SeasonGatheringId
    )
    {
        this->SeasonGatheringIdValue = SeasonGatheringId;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithTier(
        const TOptional<int64> Tier
    )
    {
        this->TierValue = Tier;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithParticipants(
        const TSharedPtr<TArray<FString>> Participants
    )
    {
        this->ParticipantsValue = Participants;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FSeasonGathering::GetSeasonGatheringId() const
    {
        return SeasonGatheringIdValue;
    }
    TOptional<FString> FSeasonGathering::GetSeasonName() const
    {
        return SeasonNameValue;
    }
    TOptional<int64> FSeasonGathering::GetSeason() const
    {
        return SeasonValue;
    }

    FString FSeasonGathering::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<int64> FSeasonGathering::GetTier() const
    {
        return TierValue;
    }

    FString FSeasonGathering::GetTierString() const
    {
        if (!TierValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TierValue.GetValue());
    }
    TOptional<FString> FSeasonGathering::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<FString>> FSeasonGathering::GetParticipants() const
    {
        return ParticipantsValue;
    }
    TOptional<int64> FSeasonGathering::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSeasonGathering::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FSeasonGathering::GetRevision() const
    {
        return RevisionValue;
    }

    FString FSeasonGathering::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FSeasonGathering::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):(?<tier>.+):gathering:(?<seasonGatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonGathering::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):(?<tier>.+):gathering:(?<seasonGatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonGathering::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):(?<tier>.+):gathering:(?<seasonGatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonGathering::GetSeasonNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):(?<tier>.+):gathering:(?<seasonGatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonGathering::GetSeasonFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):(?<tier>.+):gathering:(?<seasonGatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonGathering::GetTierFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):(?<tier>.+):gathering:(?<seasonGatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonGathering::GetSeasonGatheringNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):(?<tier>.+):gathering:(?<seasonGatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(7);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSeasonGathering> FSeasonGathering::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSeasonGathering>()
            ->WithSeasonGatheringId(Data->HasField(ANSI_TO_TCHAR("seasonGatheringId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("seasonGatheringId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSeasonName(Data->HasField(ANSI_TO_TCHAR("seasonName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("seasonName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSeason(Data->HasField(ANSI_TO_TCHAR("season")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("season"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithTier(Data->HasField(ANSI_TO_TCHAR("tier")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("tier"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithParticipants(Data->HasField(ANSI_TO_TCHAR("participants")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("participants")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("participants")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("participants")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FSeasonGathering::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SeasonGatheringIdValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonGatheringId", SeasonGatheringIdValue.GetValue());
        }
        if (SeasonNameValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonName", SeasonNameValue.GetValue());
        }
        if (SeasonValue.IsSet())
        {
            JsonRootObject->SetStringField("season", FString::Printf(TEXT("%lld"), SeasonValue.GetValue()));
        }
        if (TierValue.IsSet())
        {
            JsonRootObject->SetStringField("tier", FString::Printf(TEXT("%lld"), TierValue.GetValue()));
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ParticipantsValue != nullptr && ParticipantsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParticipantsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("participants", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FSeasonGathering::TypeName = "SeasonGathering";
}