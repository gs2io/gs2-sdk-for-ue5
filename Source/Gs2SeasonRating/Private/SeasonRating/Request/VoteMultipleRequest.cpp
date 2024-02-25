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

#include "SeasonRating/Request/VoteMultipleRequest.h"

namespace Gs2::SeasonRating::Request
{
    FVoteMultipleRequest::FVoteMultipleRequest():
        NamespaceNameValue(TOptional<FString>()),
        SignedBallotsValue(nullptr),
        GameResultsValue(nullptr),
        KeyIdValue(TOptional<FString>())
    {
    }

    FVoteMultipleRequest::FVoteMultipleRequest(
        const FVoteMultipleRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SignedBallotsValue(From.SignedBallotsValue),
        GameResultsValue(From.GameResultsValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FVoteMultipleRequest> FVoteMultipleRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVoteMultipleRequest> FVoteMultipleRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVoteMultipleRequest> FVoteMultipleRequest::WithSignedBallots(
        const TSharedPtr<TArray<TSharedPtr<Model::FSignedBallot>>> SignedBallots
    )
    {
        this->SignedBallotsValue = SignedBallots;
        return SharedThis(this);
    }

    TSharedPtr<FVoteMultipleRequest> FVoteMultipleRequest::WithGameResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResults
    )
    {
        this->GameResultsValue = GameResults;
        return SharedThis(this);
    }

    TSharedPtr<FVoteMultipleRequest> FVoteMultipleRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FVoteMultipleRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVoteMultipleRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSignedBallot>>> FVoteMultipleRequest::GetSignedBallots() const
    {
        if (!SignedBallotsValue.IsValid())
        {
            return nullptr;
        }
        return SignedBallotsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> FVoteMultipleRequest::GetGameResults() const
    {
        if (!GameResultsValue.IsValid())
        {
            return nullptr;
        }
        return GameResultsValue;
    }

    TOptional<FString> FVoteMultipleRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FVoteMultipleRequest> FVoteMultipleRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVoteMultipleRequest>()
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
          ->WithSignedBallots(Data->HasField("signedBallots") ? [Data]() -> TSharedPtr<TArray<Model::FSignedBallotPtr>>
              {
                  auto v = MakeShared<TArray<Model::FSignedBallotPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("signedBallots") && Data->HasTypedField<EJson::Array>("signedBallots"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("signedBallots"))
                      {
                          v->Add(Model::FSignedBallot::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FSignedBallotPtr>>())
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
              }() : MakeShared<TArray<Model::FGameResultPtr>>())
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

    TSharedPtr<FJsonObject> FVoteMultipleRequest::ToJson() const
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
        if (SignedBallotsValue != nullptr && SignedBallotsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SignedBallotsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("signedBallots", v);
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