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

#include "Matchmaking/Request/VerifyIncludeParticipantRequest.h"

namespace Gs2::Matchmaking::Request
{
    FVerifyIncludeParticipantRequest::FVerifyIncludeParticipantRequest():
        NamespaceNameValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        SeasonValue(TOptional<int64>()),
        TierValue(TOptional<int64>()),
        SeasonGatheringNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>())
    {
    }

    FVerifyIncludeParticipantRequest::FVerifyIncludeParticipantRequest(
        const FVerifyIncludeParticipantRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SeasonNameValue(From.SeasonNameValue),
        SeasonValue(From.SeasonValue),
        TierValue(From.TierValue),
        SeasonGatheringNameValue(From.SeasonGatheringNameValue),
        AccessTokenValue(From.AccessTokenValue),
        VerifyTypeValue(From.VerifyTypeValue)
    {
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithTier(
        const TOptional<int64> Tier
    )
    {
        this->TierValue = Tier;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithSeasonGatheringName(
        const TOptional<FString> SeasonGatheringName
    )
    {
        this->SeasonGatheringNameValue = SeasonGatheringName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyIncludeParticipantRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyIncludeParticipantRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyIncludeParticipantRequest::GetSeasonName() const
    {
        return SeasonNameValue;
    }

    TOptional<int64> FVerifyIncludeParticipantRequest::GetSeason() const
    {
        return SeasonValue;
    }

    FString FVerifyIncludeParticipantRequest::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }

    TOptional<int64> FVerifyIncludeParticipantRequest::GetTier() const
    {
        return TierValue;
    }

    FString FVerifyIncludeParticipantRequest::GetTierString() const
    {
        if (!TierValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TierValue.GetValue());
    }

    TOptional<FString> FVerifyIncludeParticipantRequest::GetSeasonGatheringName() const
    {
        return SeasonGatheringNameValue;
    }

    TOptional<FString> FVerifyIncludeParticipantRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyIncludeParticipantRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<FString> FVerifyIncludeParticipantRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyIncludeParticipantRequest> FVerifyIncludeParticipantRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyIncludeParticipantRequest>()
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
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyIncludeParticipantRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}