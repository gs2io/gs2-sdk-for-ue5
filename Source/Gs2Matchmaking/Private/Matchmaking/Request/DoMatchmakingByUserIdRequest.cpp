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

#include "Matchmaking/Request/DoMatchmakingByUserIdRequest.h"

namespace Gs2::Matchmaking::Request
{
    FDoMatchmakingByUserIdRequest::FDoMatchmakingByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        PlayerValue(nullptr),
        MatchmakingContextTokenValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FDoMatchmakingByUserIdRequest::FDoMatchmakingByUserIdRequest(
        const FDoMatchmakingByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        PlayerValue(From.PlayerValue),
        MatchmakingContextTokenValue(From.MatchmakingContextTokenValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::WithPlayer(
        const TSharedPtr<Model::FPlayer> Player
    )
    {
        this->PlayerValue = Player;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::WithMatchmakingContextToken(
        const TOptional<FString> MatchmakingContextToken
    )
    {
        this->MatchmakingContextTokenValue = MatchmakingContextToken;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDoMatchmakingByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDoMatchmakingByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDoMatchmakingByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<Model::FPlayer> FDoMatchmakingByUserIdRequest::GetPlayer() const
    {
        if (!PlayerValue.IsValid())
        {
            return nullptr;
        }
        return PlayerValue;
    }

    TOptional<FString> FDoMatchmakingByUserIdRequest::GetMatchmakingContextToken() const
    {
        return MatchmakingContextTokenValue;
    }

    TOptional<FString> FDoMatchmakingByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FDoMatchmakingByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDoMatchmakingByUserIdRequest> FDoMatchmakingByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDoMatchmakingByUserIdRequest>()
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
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithPlayer(Data->HasField(ANSI_TO_TCHAR("player")) ? [Data]() -> Model::FPlayerPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("player")))
                  {
                      return nullptr;
                  }
                  return Model::FPlayer::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("player")));
              }() : nullptr)
            ->WithMatchmakingContextToken(Data->HasField(ANSI_TO_TCHAR("matchmakingContextToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("matchmakingContextToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDoMatchmakingByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (PlayerValue != nullptr && PlayerValue.IsValid())
        {
            JsonRootObject->SetObjectField("player", PlayerValue->ToJson());
        }
        if (MatchmakingContextTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("matchmakingContextToken", MatchmakingContextTokenValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}