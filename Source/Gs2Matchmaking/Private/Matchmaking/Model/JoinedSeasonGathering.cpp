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

#include "Matchmaking/Model/JoinedSeasonGathering.h"

namespace Gs2::Matchmaking::Model
{
    FJoinedSeasonGathering::FJoinedSeasonGathering():
        JoinedSeasonGatheringIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        TierValue(TOptional<int64>()),
        SeasonGatheringNameValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FJoinedSeasonGathering::FJoinedSeasonGathering(
        const FJoinedSeasonGathering& From
    ):
        JoinedSeasonGatheringIdValue(From.JoinedSeasonGatheringIdValue),
        UserIdValue(From.UserIdValue),
        SeasonNameValue(From.SeasonNameValue),
        SeasonValue(From.SeasonValue),
        TierValue(From.TierValue),
        SeasonGatheringNameValue(From.SeasonGatheringNameValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::WithJoinedSeasonGatheringId(
        const TOptional<FString> JoinedSeasonGatheringId
    )
    {
        this->JoinedSeasonGatheringIdValue = JoinedSeasonGatheringId;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::WithTier(
        const TOptional<int64> Tier
    )
    {
        this->TierValue = Tier;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::WithSeasonGatheringName(
        const TOptional<FString> SeasonGatheringName
    )
    {
        this->SeasonGatheringNameValue = SeasonGatheringName;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FJoinedSeasonGathering::GetJoinedSeasonGatheringId() const
    {
        return JoinedSeasonGatheringIdValue;
    }
    TOptional<FString> FJoinedSeasonGathering::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FJoinedSeasonGathering::GetSeasonName() const
    {
        return SeasonNameValue;
    }
    TOptional<int64> FJoinedSeasonGathering::GetSeason() const
    {
        return SeasonValue;
    }

    FString FJoinedSeasonGathering::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<int64> FJoinedSeasonGathering::GetTier() const
    {
        return TierValue;
    }

    FString FJoinedSeasonGathering::GetTierString() const
    {
        if (!TierValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TierValue.GetValue());
    }
    TOptional<FString> FJoinedSeasonGathering::GetSeasonGatheringName() const
    {
        return SeasonGatheringNameValue;
    }
    TOptional<int64> FJoinedSeasonGathering::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FJoinedSeasonGathering::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FJoinedSeasonGathering::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):user:(?<userId>.+):joinedGathering"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedSeasonGathering::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):user:(?<userId>.+):joinedGathering"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedSeasonGathering::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):user:(?<userId>.+):joinedGathering"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedSeasonGathering::GetSeasonNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):user:(?<userId>.+):joinedGathering"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedSeasonGathering::GetSeasonFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):user:(?<userId>.+):joinedGathering"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedSeasonGathering::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):season:(?<seasonName>.+):(?<season>.+):user:(?<userId>.+):joinedGathering"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FJoinedSeasonGathering> FJoinedSeasonGathering::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FJoinedSeasonGathering>()
            ->WithJoinedSeasonGatheringId(Data->HasField(ANSI_TO_TCHAR("joinedSeasonGatheringId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("joinedSeasonGatheringId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
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
            ->WithSeasonGatheringName(Data->HasField(ANSI_TO_TCHAR("seasonGatheringName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("seasonGatheringName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FJoinedSeasonGathering::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (JoinedSeasonGatheringIdValue.IsSet())
        {
            JsonRootObject->SetStringField("joinedSeasonGatheringId", JoinedSeasonGatheringIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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
        if (SeasonGatheringNameValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonGatheringName", SeasonGatheringNameValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FJoinedSeasonGathering::TypeName = "JoinedSeasonGathering";
}