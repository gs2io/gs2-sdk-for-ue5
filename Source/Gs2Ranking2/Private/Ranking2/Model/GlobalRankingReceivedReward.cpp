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

#include "Ranking2/Model/GlobalRankingReceivedReward.h"

namespace Gs2::Ranking2::Model
{
    FGlobalRankingReceivedReward::FGlobalRankingReceivedReward():
        GlobalRankingReceivedRewardIdValue(TOptional<FString>()),
        RankingNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        ReceivedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FGlobalRankingReceivedReward::FGlobalRankingReceivedReward(
        const FGlobalRankingReceivedReward& From
    ):
        GlobalRankingReceivedRewardIdValue(From.GlobalRankingReceivedRewardIdValue),
        RankingNameValue(From.RankingNameValue),
        UserIdValue(From.UserIdValue),
        SeasonValue(From.SeasonValue),
        ReceivedAtValue(From.ReceivedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FGlobalRankingReceivedReward> FGlobalRankingReceivedReward::WithGlobalRankingReceivedRewardId(
        const TOptional<FString> GlobalRankingReceivedRewardId
    )
    {
        this->GlobalRankingReceivedRewardIdValue = GlobalRankingReceivedRewardId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingReceivedReward> FGlobalRankingReceivedReward::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingReceivedReward> FGlobalRankingReceivedReward::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingReceivedReward> FGlobalRankingReceivedReward::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingReceivedReward> FGlobalRankingReceivedReward::WithReceivedAt(
        const TOptional<int64> ReceivedAt
    )
    {
        this->ReceivedAtValue = ReceivedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingReceivedReward> FGlobalRankingReceivedReward::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FGlobalRankingReceivedReward::GetGlobalRankingReceivedRewardId() const
    {
        return GlobalRankingReceivedRewardIdValue;
    }
    TOptional<FString> FGlobalRankingReceivedReward::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<FString> FGlobalRankingReceivedReward::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FGlobalRankingReceivedReward::GetSeason() const
    {
        return SeasonValue;
    }

    FString FGlobalRankingReceivedReward::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<int64> FGlobalRankingReceivedReward::GetReceivedAt() const
    {
        return ReceivedAtValue;
    }

    FString FGlobalRankingReceivedReward::GetReceivedAtString() const
    {
        if (!ReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue());
    }
    TOptional<int64> FGlobalRankingReceivedReward::GetRevision() const
    {
        return RevisionValue;
    }

    FString FGlobalRankingReceivedReward::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FGlobalRankingReceivedReward::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):global:(?<rankingName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingReceivedReward::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):global:(?<rankingName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingReceivedReward::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):global:(?<rankingName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingReceivedReward::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):global:(?<rankingName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingReceivedReward::GetRankingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):global:(?<rankingName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGlobalRankingReceivedReward::GetSeasonFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):global:(?<rankingName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGlobalRankingReceivedReward> FGlobalRankingReceivedReward::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGlobalRankingReceivedReward>()
            ->WithGlobalRankingReceivedRewardId(Data->HasField(ANSI_TO_TCHAR("globalRankingReceivedRewardId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("globalRankingReceivedRewardId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRankingName(Data->HasField(ANSI_TO_TCHAR("rankingName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rankingName"), v))
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
            ->WithSeason(Data->HasField(ANSI_TO_TCHAR("season")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("season"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithReceivedAt(Data->HasField(ANSI_TO_TCHAR("receivedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("receivedAt"), v))
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

    TSharedPtr<FJsonObject> FGlobalRankingReceivedReward::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GlobalRankingReceivedRewardIdValue.IsSet())
        {
            JsonRootObject->SetStringField("globalRankingReceivedRewardId", GlobalRankingReceivedRewardIdValue.GetValue());
        }
        if (RankingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rankingName", RankingNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (SeasonValue.IsSet())
        {
            JsonRootObject->SetStringField("season", FString::Printf(TEXT("%lld"), SeasonValue.GetValue()));
        }
        if (ReceivedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("receivedAt", FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FGlobalRankingReceivedReward::TypeName = "GlobalRankingReceivedReward";
}