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

#include "Ranking2/Request/GetClusterRankingReceivedRewardRequest.h"

namespace Gs2::Ranking2::Request
{
    FGetClusterRankingReceivedRewardRequest::FGetClusterRankingReceivedRewardRequest():
        NamespaceNameValue(TOptional<FString>()),
        RankingNameValue(TOptional<FString>()),
        ClusterNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>())
    {
    }

    FGetClusterRankingReceivedRewardRequest::FGetClusterRankingReceivedRewardRequest(
        const FGetClusterRankingReceivedRewardRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RankingNameValue(From.RankingNameValue),
        ClusterNameValue(From.ClusterNameValue),
        AccessTokenValue(From.AccessTokenValue),
        SeasonValue(From.SeasonValue)
    {
    }

    TSharedPtr<FGetClusterRankingReceivedRewardRequest> FGetClusterRankingReceivedRewardRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetClusterRankingReceivedRewardRequest> FGetClusterRankingReceivedRewardRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetClusterRankingReceivedRewardRequest> FGetClusterRankingReceivedRewardRequest::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FGetClusterRankingReceivedRewardRequest> FGetClusterRankingReceivedRewardRequest::WithClusterName(
        const TOptional<FString> ClusterName
    )
    {
        this->ClusterNameValue = ClusterName;
        return SharedThis(this);
    }

    TSharedPtr<FGetClusterRankingReceivedRewardRequest> FGetClusterRankingReceivedRewardRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetClusterRankingReceivedRewardRequest> FGetClusterRankingReceivedRewardRequest::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TOptional<FString> FGetClusterRankingReceivedRewardRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetClusterRankingReceivedRewardRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetClusterRankingReceivedRewardRequest::GetRankingName() const
    {
        return RankingNameValue;
    }

    TOptional<FString> FGetClusterRankingReceivedRewardRequest::GetClusterName() const
    {
        return ClusterNameValue;
    }

    TOptional<FString> FGetClusterRankingReceivedRewardRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int64> FGetClusterRankingReceivedRewardRequest::GetSeason() const
    {
        return SeasonValue;
    }

    FString FGetClusterRankingReceivedRewardRequest::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }

    TSharedPtr<FGetClusterRankingReceivedRewardRequest> FGetClusterRankingReceivedRewardRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetClusterRankingReceivedRewardRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
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
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
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
              }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FGetClusterRankingReceivedRewardRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (RankingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rankingName", RankingNameValue.GetValue());
        }
        if (ClusterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("clusterName", ClusterNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (SeasonValue.IsSet())
        {
            JsonRootObject->SetStringField("season", FString::Printf(TEXT("%lld"), SeasonValue.GetValue()));
        }
        return JsonRootObject;
    }
}