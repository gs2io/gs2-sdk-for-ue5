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

#include "Matchmaking/Model/SeasonModel.h"

namespace Gs2::Matchmaking::Model
{
    FSeasonModel::FSeasonModel():
        SeasonModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MaximumParticipantsValue(TOptional<int32>()),
        ExperienceModelIdValue(TOptional<FString>()),
        ChallengePeriodEventIdValue(TOptional<FString>())
    {
    }

    FSeasonModel::FSeasonModel(
        const FSeasonModel& From
    ):
        SeasonModelIdValue(From.SeasonModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        MaximumParticipantsValue(From.MaximumParticipantsValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue)
    {
    }

    TSharedPtr<FSeasonModel> FSeasonModel::WithSeasonModelId(
        const TOptional<FString> SeasonModelId
    )
    {
        this->SeasonModelIdValue = SeasonModelId;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModel> FSeasonModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModel> FSeasonModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModel> FSeasonModel::WithMaximumParticipants(
        const TOptional<int32> MaximumParticipants
    )
    {
        this->MaximumParticipantsValue = MaximumParticipants;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModel> FSeasonModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FSeasonModel> FSeasonModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FSeasonModel::GetSeasonModelId() const
    {
        return SeasonModelIdValue;
    }
    TOptional<FString> FSeasonModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSeasonModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FSeasonModel::GetMaximumParticipants() const
    {
        return MaximumParticipantsValue;
    }

    FString FSeasonModel::GetMaximumParticipantsString() const
    {
        if (!MaximumParticipantsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumParticipantsValue.GetValue());
    }
    TOptional<FString> FSeasonModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TOptional<FString> FSeasonModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TOptional<FString> FSeasonModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSeasonModel::GetSeasonNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<seasonName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSeasonModel> FSeasonModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSeasonModel>()
            ->WithSeasonModelId(Data->HasField(ANSI_TO_TCHAR("seasonModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("seasonModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaximumParticipants(Data->HasField(ANSI_TO_TCHAR("maximumParticipants")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumParticipants"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithExperienceModelId(Data->HasField(ANSI_TO_TCHAR("experienceModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("experienceModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithChallengePeriodEventId(Data->HasField(ANSI_TO_TCHAR("challengePeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("challengePeriodEventId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSeasonModel::ToJson() const
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
        if (MaximumParticipantsValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumParticipants", MaximumParticipantsValue.GetValue());
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FSeasonModel::TypeName = "SeasonModel";
}