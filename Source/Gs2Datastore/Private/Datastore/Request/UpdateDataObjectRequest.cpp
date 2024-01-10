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

#include "Datastore/Request/UpdateDataObjectRequest.h"

namespace Gs2::Datastore::Request
{
    FUpdateDataObjectRequest::FUpdateDataObjectRequest():
        NamespaceNameValue(TOptional<FString>()),
        DataObjectNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        AllowUserIdsValue(nullptr)
    {
    }

    FUpdateDataObjectRequest::FUpdateDataObjectRequest(
        const FUpdateDataObjectRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DataObjectNameValue(From.DataObjectNameValue),
        AccessTokenValue(From.AccessTokenValue),
        ScopeValue(From.ScopeValue),
        AllowUserIdsValue(From.AllowUserIdsValue)
    {
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::WithDataObjectName(
        const TOptional<FString> DataObjectName
    )
    {
        this->DataObjectNameValue = DataObjectName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::WithAllowUserIds(
        const TSharedPtr<TArray<FString>> AllowUserIds
    )
    {
        this->AllowUserIdsValue = AllowUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateDataObjectRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateDataObjectRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateDataObjectRequest::GetDataObjectName() const
    {
        return DataObjectNameValue;
    }

    TOptional<FString> FUpdateDataObjectRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FUpdateDataObjectRequest::GetScope() const
    {
        return ScopeValue;
    }

    TSharedPtr<TArray<FString>> FUpdateDataObjectRequest::GetAllowUserIds() const
    {
        if (!AllowUserIdsValue.IsValid())
        {
            return nullptr;
        }
        return AllowUserIdsValue;
    }

    TOptional<FString> FUpdateDataObjectRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FUpdateDataObjectRequest> FUpdateDataObjectRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateDataObjectRequest>()
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
            ->WithDataObjectName(Data->HasField("dataObjectName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("dataObjectName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScope(Data->HasField("scope") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
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
              }() : MakeShared<TArray<FString>>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateDataObjectRequest::ToJson() const
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
        if (DataObjectNameValue.IsSet())
        {
            JsonRootObject->SetStringField("dataObjectName", DataObjectNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
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
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}