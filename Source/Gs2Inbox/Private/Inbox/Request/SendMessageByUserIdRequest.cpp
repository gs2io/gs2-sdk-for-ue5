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

#include "Inbox/Request/SendMessageByUserIdRequest.h"

namespace Gs2::Inbox::Request
{
    FSendMessageByUserIdRequest::FSendMessageByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReadAcquireActionsValue(nullptr),
        ExpiresAtValue(TOptional<int64>()),
        ExpiresTimeSpanValue(nullptr)
    {
    }

    FSendMessageByUserIdRequest::FSendMessageByUserIdRequest(
        const FSendMessageByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        MetadataValue(From.MetadataValue),
        ReadAcquireActionsValue(From.ReadAcquireActionsValue),
        ExpiresAtValue(From.ExpiresAtValue),
        ExpiresTimeSpanValue(From.ExpiresTimeSpanValue)
    {
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithReadAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions
    )
    {
        this->ReadAcquireActionsValue = ReadAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithExpiresTimeSpan(
        const TSharedPtr<Model::FTimeSpan> ExpiresTimeSpan
    )
    {
        this->ExpiresTimeSpanValue = ExpiresTimeSpan;
        return SharedThis(this);
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSendMessageByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSendMessageByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSendMessageByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSendMessageByUserIdRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FSendMessageByUserIdRequest::GetReadAcquireActions() const
    {
        if (!ReadAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return ReadAcquireActionsValue;
    }

    TOptional<int64> FSendMessageByUserIdRequest::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FSendMessageByUserIdRequest::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    TSharedPtr<Model::FTimeSpan> FSendMessageByUserIdRequest::GetExpiresTimeSpan() const
    {
        if (!ExpiresTimeSpanValue.IsValid())
        {
            return nullptr;
        }
        return ExpiresTimeSpanValue;
    }

    TOptional<FString> FSendMessageByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSendMessageByUserIdRequest> FSendMessageByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSendMessageByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithReadAcquireActions(Data->HasField("readAcquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("readAcquireActions") && Data->HasTypedField<EJson::Array>("readAcquireActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("readAcquireActions"))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithExpiresAt(Data->HasField("expiresAt") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("expiresAt", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
          ->WithExpiresTimeSpan(Data->HasField("expiresTimeSpan") ? [Data]() -> Model::FTimeSpanPtr
              {
                  if (Data->HasTypedField<EJson::Null>("expiresTimeSpan"))
                  {
                      return nullptr;
                  }
                  return Model::FTimeSpan::FromJson(Data->GetObjectField("expiresTimeSpan"));
              }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSendMessageByUserIdRequest::ToJson() const
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
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ReadAcquireActionsValue != nullptr && ReadAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReadAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("readAcquireActions", v);
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (ExpiresTimeSpanValue != nullptr && ExpiresTimeSpanValue.IsValid())
        {
            JsonRootObject->SetObjectField("expiresTimeSpan", ExpiresTimeSpanValue->ToJson());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}