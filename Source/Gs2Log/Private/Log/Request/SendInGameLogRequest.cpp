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

#include "Log/Request/SendInGameLogRequest.h"

namespace Gs2::Log::Request
{
    FSendInGameLogRequest::FSendInGameLogRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TagsValue(nullptr),
        PayloadValue(TOptional<FString>())
    {
    }

    FSendInGameLogRequest::FSendInGameLogRequest(
        const FSendInGameLogRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        TagsValue(From.TagsValue),
        PayloadValue(From.PayloadValue)
    {
    }

    TSharedPtr<FSendInGameLogRequest> FSendInGameLogRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSendInGameLogRequest> FSendInGameLogRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSendInGameLogRequest> FSendInGameLogRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FSendInGameLogRequest> FSendInGameLogRequest::WithTags(
        const TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> Tags
    )
    {
        this->TagsValue = Tags;
        return SharedThis(this);
    }

    TSharedPtr<FSendInGameLogRequest> FSendInGameLogRequest::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }

    TSharedPtr<FSendInGameLogRequest> FSendInGameLogRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSendInGameLogRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSendInGameLogRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSendInGameLogRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> FSendInGameLogRequest::GetTags() const
    {
        if (!TagsValue.IsValid())
        {
            return nullptr;
        }
        return TagsValue;
    }

    TOptional<FString> FSendInGameLogRequest::GetPayload() const
    {
        return PayloadValue;
    }

    TOptional<FString> FSendInGameLogRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSendInGameLogRequest> FSendInGameLogRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSendInGameLogRequest>()
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
          ->WithTags(Data->HasField(ANSI_TO_TCHAR("tags")) ? [Data]() -> TSharedPtr<TArray<Model::FInGameLogTagPtr>>
              {
                  auto v = MakeShared<TArray<Model::FInGameLogTagPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("tags")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("tags")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("tags")))
                      {
                          v->Add(Model::FInGameLogTag::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FInGameLogTagPtr>>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSendInGameLogRequest::ToJson() const
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
        if (TagsValue != nullptr && TagsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TagsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("tags", v);
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("payload", PayloadValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}