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

#include "Matchmaking/Request/PutResultRequest.h"

namespace Gs2::Matchmaking::Request
{
    FPutResultRequest::FPutResultRequest():
        NamespaceNameValue(TOptional<FString>()),
        RatingNameValue(TOptional<FString>()),
        GameResultsValue(nullptr)
    {
    }

    FPutResultRequest::FPutResultRequest(
        const FPutResultRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RatingNameValue(From.RatingNameValue),
        GameResultsValue(From.GameResultsValue)
    {
    }

    TSharedPtr<FPutResultRequest> FPutResultRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPutResultRequest> FPutResultRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPutResultRequest> FPutResultRequest::WithRatingName(
        const TOptional<FString> RatingName
    )
    {
        this->RatingNameValue = RatingName;
        return SharedThis(this);
    }

    TSharedPtr<FPutResultRequest> FPutResultRequest::WithGameResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResults
    )
    {
        this->GameResultsValue = GameResults;
        return SharedThis(this);
    }

    TOptional<FString> FPutResultRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPutResultRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPutResultRequest::GetRatingName() const
    {
        return RatingNameValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> FPutResultRequest::GetGameResults() const
    {
        if (!GameResultsValue.IsValid())
        {
            return nullptr;
        }
        return GameResultsValue;
    }

    TSharedPtr<FPutResultRequest> FPutResultRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPutResultRequest>()
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
            ->WithRatingName(Data->HasField(ANSI_TO_TCHAR("ratingName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("ratingName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithGameResults(Data->HasField(ANSI_TO_TCHAR("gameResults")) ? [Data]() -> TSharedPtr<TArray<Model::FGameResultPtr>>
              {
                  auto v = MakeShared<TArray<Model::FGameResultPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("gameResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("gameResults")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("gameResults")))
                      {
                          v->Add(Model::FGameResult::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FGameResultPtr>>());
    }

    TSharedPtr<FJsonObject> FPutResultRequest::ToJson() const
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
        if (RatingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("ratingName", RatingNameValue.GetValue());
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
        return JsonRootObject;
    }
}