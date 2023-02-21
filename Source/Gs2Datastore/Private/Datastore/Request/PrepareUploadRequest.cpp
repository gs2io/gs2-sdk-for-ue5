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

#include "Datastore/Request/PrepareUploadRequest.h"

namespace Gs2::Datastore::Request
{
    FPrepareUploadRequest::FPrepareUploadRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        ContentTypeValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        AllowUserIdsValue(nullptr),
        UpdateIfExistsValue(TOptional<bool>())
    {
    }

    FPrepareUploadRequest::FPrepareUploadRequest(
        const FPrepareUploadRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        NameValue(From.NameValue),
        ContentTypeValue(From.ContentTypeValue),
        ScopeValue(From.ScopeValue),
        AllowUserIdsValue(From.AllowUserIdsValue),
        UpdateIfExistsValue(From.UpdateIfExistsValue)
    {
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithContentType(
        const TOptional<FString> ContentType
    )
    {
        this->ContentTypeValue = ContentType;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithAllowUserIds(
        const TSharedPtr<TArray<FString>> AllowUserIds
    )
    {
        this->AllowUserIdsValue = AllowUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithUpdateIfExists(
        const TOptional<bool> UpdateIfExists
    )
    {
        this->UpdateIfExistsValue = UpdateIfExists;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareUploadRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPrepareUploadRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPrepareUploadRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FPrepareUploadRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FPrepareUploadRequest::GetContentType() const
    {
        return ContentTypeValue;
    }

    TOptional<FString> FPrepareUploadRequest::GetScope() const
    {
        return ScopeValue;
    }

    TSharedPtr<TArray<FString>> FPrepareUploadRequest::GetAllowUserIds() const
    {
        if (!AllowUserIdsValue.IsValid())
        {
            return nullptr;
        }
        return AllowUserIdsValue;
    }

    TOptional<bool> FPrepareUploadRequest::GetUpdateIfExists() const
    {
        return UpdateIfExistsValue;
    }

    FString FPrepareUploadRequest::GetUpdateIfExistsString() const
    {
        if (!UpdateIfExistsValue.IsSet())
        {
            return FString("null");
        }
        return FString(UpdateIfExistsValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FPrepareUploadRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPrepareUploadRequest> FPrepareUploadRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareUploadRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithContentType(Data->HasField("contentType") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("contentType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScope(Data->HasField("scope") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("scope", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAllowUserIds(Data->HasField("allowUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("allowUserIds") && Data->HasTypedField<EJson::Array>("allowUserIds"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("allowUserIds"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithUpdateIfExists(Data->HasField("updateIfExists") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("updateIfExists", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareUploadRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ContentTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("contentType", ContentTypeValue.GetValue());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField("scope", ScopeValue.GetValue());
        }
        if (AllowUserIdsValue != nullptr && AllowUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AllowUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("allowUserIds", v);
        }
        if (UpdateIfExistsValue.IsSet())
        {
            JsonRootObject->SetBoolField("updateIfExists", UpdateIfExistsValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}