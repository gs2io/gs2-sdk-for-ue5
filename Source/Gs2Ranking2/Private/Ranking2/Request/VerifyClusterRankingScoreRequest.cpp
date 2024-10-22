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

#include "Ranking2/Request/VerifyClusterRankingScoreRequest.h"

namespace Gs2::Ranking2::Request
{
    FVerifyClusterRankingScoreRequest::FVerifyClusterRankingScoreRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        RankingNameValue(TOptional<FString>()),
        ClusterNameValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        ScoreValue(TOptional<int64>()),
        MultiplyValueSpecifyingQuantityValue(TOptional<bool>())
    {
    }

    FVerifyClusterRankingScoreRequest::FVerifyClusterRankingScoreRequest(
        const FVerifyClusterRankingScoreRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        RankingNameValue(From.RankingNameValue),
        ClusterNameValue(From.ClusterNameValue),
        VerifyTypeValue(From.VerifyTypeValue),
        SeasonValue(From.SeasonValue),
        ScoreValue(From.ScoreValue),
        MultiplyValueSpecifyingQuantityValue(From.MultiplyValueSpecifyingQuantityValue)
    {
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithClusterName(
        const TOptional<FString> ClusterName
    )
    {
        this->ClusterNameValue = ClusterName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithMultiplyValueSpecifyingQuantity(
        const TOptional<bool> MultiplyValueSpecifyingQuantity
    )
    {
        this->MultiplyValueSpecifyingQuantityValue = MultiplyValueSpecifyingQuantity;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyClusterRankingScoreRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyClusterRankingScoreRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyClusterRankingScoreRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyClusterRankingScoreRequest::GetRankingName() const
    {
        return RankingNameValue;
    }

    TOptional<FString> FVerifyClusterRankingScoreRequest::GetClusterName() const
    {
        return ClusterNameValue;
    }

    TOptional<FString> FVerifyClusterRankingScoreRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int64> FVerifyClusterRankingScoreRequest::GetSeason() const
    {
        return SeasonValue;
    }

    FString FVerifyClusterRankingScoreRequest::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }

    TOptional<int64> FVerifyClusterRankingScoreRequest::GetScore() const
    {
        return ScoreValue;
    }

    FString FVerifyClusterRankingScoreRequest::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }

    TOptional<bool> FVerifyClusterRankingScoreRequest::GetMultiplyValueSpecifyingQuantity() const
    {
        return MultiplyValueSpecifyingQuantityValue;
    }

    FString FVerifyClusterRankingScoreRequest::GetMultiplyValueSpecifyingQuantityString() const
    {
        if (!MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            return FString("null");
        }
        return FString(MultiplyValueSpecifyingQuantityValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FVerifyClusterRankingScoreRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyClusterRankingScoreRequest> FVerifyClusterRankingScoreRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyClusterRankingScoreRequest>()
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
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
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
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
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
            ->WithScore(Data->HasField(ANSI_TO_TCHAR("score")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("score"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMultiplyValueSpecifyingQuantity(Data->HasField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("multiplyValueSpecifyingQuantity"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyClusterRankingScoreRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (RankingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rankingName", RankingNameValue.GetValue());
        }
        if (ClusterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("clusterName", ClusterNameValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (SeasonValue.IsSet())
        {
            JsonRootObject->SetStringField("season", FString::Printf(TEXT("%lld"), SeasonValue.GetValue()));
        }
        if (ScoreValue.IsSet())
        {
            JsonRootObject->SetStringField("score", FString::Printf(TEXT("%lld"), ScoreValue.GetValue()));
        }
        if (MultiplyValueSpecifyingQuantityValue.IsSet())
        {
            JsonRootObject->SetBoolField("multiplyValueSpecifyingQuantity", MultiplyValueSpecifyingQuantityValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}