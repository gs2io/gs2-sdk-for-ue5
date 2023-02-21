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

#include "Matchmaking/Request/DoMatchmakingByPlayerRequest.h"

namespace Gs2::Matchmaking::Request
{
    FDoMatchmakingByPlayerRequest::FDoMatchmakingByPlayerRequest():
        NamespaceNameValue(TOptional<FString>()),
        PlayerValue(nullptr),
        MatchmakingContextTokenValue(TOptional<FString>())
    {
    }

    FDoMatchmakingByPlayerRequest::FDoMatchmakingByPlayerRequest(
        const FDoMatchmakingByPlayerRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        PlayerValue(From.PlayerValue),
        MatchmakingContextTokenValue(From.MatchmakingContextTokenValue)
    {
    }

    TSharedPtr<FDoMatchmakingByPlayerRequest> FDoMatchmakingByPlayerRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByPlayerRequest> FDoMatchmakingByPlayerRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByPlayerRequest> FDoMatchmakingByPlayerRequest::WithPlayer(
        const TSharedPtr<Model::FPlayer> Player
    )
    {
        this->PlayerValue = Player;
        return SharedThis(this);
    }

    TSharedPtr<FDoMatchmakingByPlayerRequest> FDoMatchmakingByPlayerRequest::WithMatchmakingContextToken(
        const TOptional<FString> MatchmakingContextToken
    )
    {
        this->MatchmakingContextTokenValue = MatchmakingContextToken;
        return SharedThis(this);
    }

    TOptional<FString> FDoMatchmakingByPlayerRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDoMatchmakingByPlayerRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<Model::FPlayer> FDoMatchmakingByPlayerRequest::GetPlayer() const
    {
        if (!PlayerValue.IsValid())
        {
            return nullptr;
        }
        return PlayerValue;
    }

    TOptional<FString> FDoMatchmakingByPlayerRequest::GetMatchmakingContextToken() const
    {
        return MatchmakingContextTokenValue;
    }

    TSharedPtr<FDoMatchmakingByPlayerRequest> FDoMatchmakingByPlayerRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDoMatchmakingByPlayerRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithPlayer(Data->HasField("player") ? [Data]() -> Model::FPlayerPtr
              {
                  if (Data->HasTypedField<EJson::Null>("player"))
                  {
                      return nullptr;
                  }
                  return Model::FPlayer::FromJson(Data->GetObjectField("player"));
             }() : nullptr)
            ->WithMatchmakingContextToken(Data->HasField("matchmakingContextToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("matchmakingContextToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDoMatchmakingByPlayerRequest::ToJson() const
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
        if (PlayerValue != nullptr && PlayerValue.IsValid())
        {
            JsonRootObject->SetObjectField("player", PlayerValue->ToJson());
        }
        if (MatchmakingContextTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("matchmakingContextToken", MatchmakingContextTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}