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

#include "Ranking2/Model/ClusterRankingReceivedReward.h"

namespace Gs2::Ranking2::Model
{
    FClusterRankingReceivedReward::FClusterRankingReceivedReward():
        ClusterRankingReceivedRewardIdValue(TOptional<FString>()),
        RankingNameValue(TOptional<FString>()),
        ClusterNameValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        UserIdValue(TOptional<FString>()),
        ReceivedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FClusterRankingReceivedReward::FClusterRankingReceivedReward(
        const FClusterRankingReceivedReward& From
    ):
        ClusterRankingReceivedRewardIdValue(From.ClusterRankingReceivedRewardIdValue),
        RankingNameValue(From.RankingNameValue),
        ClusterNameValue(From.ClusterNameValue),
        SeasonValue(From.SeasonValue),
        UserIdValue(From.UserIdValue),
        ReceivedAtValue(From.ReceivedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::WithClusterRankingReceivedRewardId(
        const TOptional<FString> ClusterRankingReceivedRewardId
    )
    {
        this->ClusterRankingReceivedRewardIdValue = ClusterRankingReceivedRewardId;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::WithClusterName(
        const TOptional<FString> ClusterName
    )
    {
        this->ClusterNameValue = ClusterName;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::WithReceivedAt(
        const TOptional<int64> ReceivedAt
    )
    {
        this->ReceivedAtValue = ReceivedAt;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FClusterRankingReceivedReward::GetClusterRankingReceivedRewardId() const
    {
        return ClusterRankingReceivedRewardIdValue;
    }
    TOptional<FString> FClusterRankingReceivedReward::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<FString> FClusterRankingReceivedReward::GetClusterName() const
    {
        return ClusterNameValue;
    }
    TOptional<int64> FClusterRankingReceivedReward::GetSeason() const
    {
        return SeasonValue;
    }

    FString FClusterRankingReceivedReward::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FClusterRankingReceivedReward::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FClusterRankingReceivedReward::GetReceivedAt() const
    {
        return ReceivedAtValue;
    }

    FString FClusterRankingReceivedReward::GetReceivedAtString() const
    {
        if (!ReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue());
    }
    TOptional<int64> FClusterRankingReceivedReward::GetRevision() const
    {
        return RevisionValue;
    }

    FString FClusterRankingReceivedReward::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FClusterRankingReceivedReward::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):cluster:(?<rankingName>.+):(?<clusterName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingReceivedReward::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):cluster:(?<rankingName>.+):(?<clusterName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingReceivedReward::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):cluster:(?<rankingName>.+):(?<clusterName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingReceivedReward::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):cluster:(?<rankingName>.+):(?<clusterName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingReceivedReward::GetRankingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):cluster:(?<rankingName>.+):(?<clusterName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingReceivedReward::GetClusterNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):cluster:(?<rankingName>.+):(?<clusterName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingReceivedReward::GetSeasonFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):user:(?<userId>.+):cluster:(?<rankingName>.+):(?<clusterName>.+):(?<season>.+):reward:received"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(7);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FClusterRankingReceivedReward> FClusterRankingReceivedReward::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FClusterRankingReceivedReward>()
            ->WithClusterRankingReceivedRewardId(Data->HasField(ANSI_TO_TCHAR("clusterRankingReceivedRewardId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("clusterRankingReceivedRewardId"), v))
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
            ->WithClusterName(Data->HasField(ANSI_TO_TCHAR("clusterName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("clusterName"), v))
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
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FClusterRankingReceivedReward::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ClusterRankingReceivedRewardIdValue.IsSet())
        {
            JsonRootObject->SetStringField("clusterRankingReceivedRewardId", ClusterRankingReceivedRewardIdValue.GetValue());
        }
        if (RankingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rankingName", RankingNameValue.GetValue());
        }
        if (ClusterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("clusterName", ClusterNameValue.GetValue());
        }
        if (SeasonValue.IsSet())
        {
            JsonRootObject->SetStringField("season", FString::Printf(TEXT("%lld"), SeasonValue.GetValue()));
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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

    FString FClusterRankingReceivedReward::TypeName = "ClusterRankingReceivedReward";
}