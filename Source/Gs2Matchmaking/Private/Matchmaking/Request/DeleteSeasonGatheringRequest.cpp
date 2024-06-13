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

#include "Matchmaking/Request/DeleteSeasonGatheringRequest.h"

namespace Gs2::Matchmaking::Request
{
    FDeleteSeasonGatheringRequest::FDeleteSeasonGatheringRequest():
        NamespaceNameValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        TierValue(TOptional<int64>()),
        SeasonGatheringNameValue(TOptional<FString>())
    {
    }

    FDeleteSeasonGatheringRequest::FDeleteSeasonGatheringRequest(
        const FDeleteSeasonGatheringRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SeasonNameValue(From.SeasonNameValue),
        SeasonValue(From.SeasonValue),
        TierValue(From.TierValue),
        SeasonGatheringNameValue(From.SeasonGatheringNameValue)
    {
    }

    TSharedPtr<FDeleteSeasonGatheringRequest> FDeleteSeasonGatheringRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteSeasonGatheringRequest> FDeleteSeasonGatheringRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteSeasonGatheringRequest> FDeleteSeasonGatheringRequest::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteSeasonGatheringRequest> FDeleteSeasonGatheringRequest::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteSeasonGatheringRequest> FDeleteSeasonGatheringRequest::WithTier(
        const TOptional<int64> Tier
    )
    {
        this->TierValue = Tier;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteSeasonGatheringRequest> FDeleteSeasonGatheringRequest::WithSeasonGatheringName(
        const TOptional<FString> SeasonGatheringName
    )
    {
        this->SeasonGatheringNameValue = SeasonGatheringName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteSeasonGatheringRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteSeasonGatheringRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteSeasonGatheringRequest::GetSeasonName() const
    {
        return SeasonNameValue;
    }

    TOptional<int64> FDeleteSeasonGatheringRequest::GetSeason() const
    {
        return SeasonValue;
    }

    FString FDeleteSeasonGatheringRequest::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }

    TOptional<int64> FDeleteSeasonGatheringRequest::GetTier() const
    {
        return TierValue;
    }

    FString FDeleteSeasonGatheringRequest::GetTierString() const
    {
        if (!TierValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TierValue.GetValue());
    }

    TOptional<FString> FDeleteSeasonGatheringRequest::GetSeasonGatheringName() const
    {
        return SeasonGatheringNameValue;
    }

    TSharedPtr<FDeleteSeasonGatheringRequest> FDeleteSeasonGatheringRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteSeasonGatheringRequest>()
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteSeasonGatheringRequest::ToJson() const
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
        return JsonRootObject;
    }
}