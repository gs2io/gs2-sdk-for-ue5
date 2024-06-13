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

#include "Matchmaking/Request/GetJoinedSeasonGatheringRequest.h"

namespace Gs2::Matchmaking::Request
{
    FGetJoinedSeasonGatheringRequest::FGetJoinedSeasonGatheringRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>())
    {
    }

    FGetJoinedSeasonGatheringRequest::FGetJoinedSeasonGatheringRequest(
        const FGetJoinedSeasonGatheringRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        SeasonNameValue(From.SeasonNameValue),
        SeasonValue(From.SeasonValue)
    {
    }

    TSharedPtr<FGetJoinedSeasonGatheringRequest> FGetJoinedSeasonGatheringRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetJoinedSeasonGatheringRequest> FGetJoinedSeasonGatheringRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetJoinedSeasonGatheringRequest> FGetJoinedSeasonGatheringRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetJoinedSeasonGatheringRequest> FGetJoinedSeasonGatheringRequest::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FGetJoinedSeasonGatheringRequest> FGetJoinedSeasonGatheringRequest::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TOptional<FString> FGetJoinedSeasonGatheringRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetJoinedSeasonGatheringRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetJoinedSeasonGatheringRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FGetJoinedSeasonGatheringRequest::GetSeasonName() const
    {
        return SeasonNameValue;
    }

    TOptional<int64> FGetJoinedSeasonGatheringRequest::GetSeason() const
    {
        return SeasonValue;
    }

    FString FGetJoinedSeasonGatheringRequest::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }

    TSharedPtr<FGetJoinedSeasonGatheringRequest> FGetJoinedSeasonGatheringRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetJoinedSeasonGatheringRequest>()
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
              }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FGetJoinedSeasonGatheringRequest::ToJson() const
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
        if (SeasonNameValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonName", SeasonNameValue.GetValue());
        }
        if (SeasonValue.IsSet())
        {
            JsonRootObject->SetStringField("season", FString::Printf(TEXT("%lld"), SeasonValue.GetValue()));
        }
        return JsonRootObject;
    }
}