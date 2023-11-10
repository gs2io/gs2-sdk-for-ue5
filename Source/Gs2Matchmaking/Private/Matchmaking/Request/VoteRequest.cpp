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

#include "Matchmaking/Request/VoteRequest.h"

namespace Gs2::Matchmaking::Request
{
    FVoteRequest::FVoteRequest():
        NamespaceNameValue(TOptional<FString>()),
        BallotBodyValue(TOptional<FString>()),
        BallotSignatureValue(TOptional<FString>()),
        GameResultsValue(nullptr),
        KeyIdValue(TOptional<FString>())
    {
    }

    FVoteRequest::FVoteRequest(
        const FVoteRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BallotBodyValue(From.BallotBodyValue),
        BallotSignatureValue(From.BallotSignatureValue),
        GameResultsValue(From.GameResultsValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FVoteRequest> FVoteRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVoteRequest> FVoteRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVoteRequest> FVoteRequest::WithBallotBody(
        const TOptional<FString> BallotBody
    )
    {
        this->BallotBodyValue = BallotBody;
        return SharedThis(this);
    }

    TSharedPtr<FVoteRequest> FVoteRequest::WithBallotSignature(
        const TOptional<FString> BallotSignature
    )
    {
        this->BallotSignatureValue = BallotSignature;
        return SharedThis(this);
    }

    TSharedPtr<FVoteRequest> FVoteRequest::WithGameResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResults
    )
    {
        this->GameResultsValue = GameResults;
        return SharedThis(this);
    }

    TSharedPtr<FVoteRequest> FVoteRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FVoteRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVoteRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVoteRequest::GetBallotBody() const
    {
        return BallotBodyValue;
    }

    TOptional<FString> FVoteRequest::GetBallotSignature() const
    {
        return BallotSignatureValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> FVoteRequest::GetGameResults() const
    {
        if (!GameResultsValue.IsValid())
        {
            return nullptr;
        }
        return GameResultsValue;
    }

    TOptional<FString> FVoteRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FVoteRequest> FVoteRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVoteRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBallotBody(Data->HasField("ballotBody") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("ballotBody", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBallotSignature(Data->HasField("ballotSignature") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("ballotSignature", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithGameResults(Data->HasField("gameResults") ? [Data]() -> TSharedPtr<TArray<Model::FGameResultPtr>>
              {
                  auto v = MakeShared<TArray<Model::FGameResultPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("gameResults") && Data->HasTypedField<EJson::Array>("gameResults"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("gameResults"))
                      {
                          v->Add(Model::FGameResult::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVoteRequest::ToJson() const
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
        if (BallotBodyValue.IsSet())
        {
            JsonRootObject->SetStringField("ballotBody", BallotBodyValue.GetValue());
        }
        if (BallotSignatureValue.IsSet())
        {
            JsonRootObject->SetStringField("ballotSignature", BallotSignatureValue.GetValue());
        }
        if (GameResultsValue != nullptr && GameResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *GameResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("gameResults", v);
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}