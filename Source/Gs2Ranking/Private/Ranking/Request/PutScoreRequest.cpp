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

#include "Ranking/Request/PutScoreRequest.h"

namespace Gs2::Ranking::Request
{
    FPutScoreRequest::FPutScoreRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        ScoreValue(TOptional<int64>()),
        MetadataValue(TOptional<FString>())
    {
    }

    FPutScoreRequest::FPutScoreRequest(
        const FPutScoreRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue),
        AccessTokenValue(From.AccessTokenValue),
        ScoreValue(From.ScoreValue),
        MetadataValue(From.MetadataValue)
    {
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPutScoreRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPutScoreRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPutScoreRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<FString> FPutScoreRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int64> FPutScoreRequest::GetScore() const
    {
        return ScoreValue;
    }

    FString FPutScoreRequest::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }

    TOptional<FString> FPutScoreRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FPutScoreRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPutScoreRequest> FPutScoreRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPutScoreRequest>()
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
            ->WithCategoryName(Data->HasField("categoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("categoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScore(Data->HasField("score") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("score", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPutScoreRequest::ToJson() const
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
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (ScoreValue.IsSet())
        {
            JsonRootObject->SetStringField("score", FString::Printf(TEXT("%lld"), ScoreValue.GetValue()));
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}