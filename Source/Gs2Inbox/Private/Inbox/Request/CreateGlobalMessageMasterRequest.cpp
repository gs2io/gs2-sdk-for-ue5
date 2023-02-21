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

#include "Inbox/Request/CreateGlobalMessageMasterRequest.h"

namespace Gs2::Inbox::Request
{
    FCreateGlobalMessageMasterRequest::FCreateGlobalMessageMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReadAcquireActionsValue(nullptr),
        ExpiresTimeSpanValue(nullptr),
        ExpiresAtValue(TOptional<int64>())
    {
    }

    FCreateGlobalMessageMasterRequest::FCreateGlobalMessageMasterRequest(
        const FCreateGlobalMessageMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ReadAcquireActionsValue(From.ReadAcquireActionsValue),
        ExpiresTimeSpanValue(From.ExpiresTimeSpanValue),
        ExpiresAtValue(From.ExpiresAtValue)
    {
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::WithReadAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions
    )
    {
        this->ReadAcquireActionsValue = ReadAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::WithExpiresTimeSpan(
        const TSharedPtr<Model::FTimeSpan> ExpiresTimeSpan
    )
    {
        this->ExpiresTimeSpanValue = ExpiresTimeSpan;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TOptional<FString> FCreateGlobalMessageMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateGlobalMessageMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateGlobalMessageMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateGlobalMessageMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FCreateGlobalMessageMasterRequest::GetReadAcquireActions() const
    {
        if (!ReadAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return ReadAcquireActionsValue;
    }

    TSharedPtr<Model::FTimeSpan> FCreateGlobalMessageMasterRequest::GetExpiresTimeSpan() const
    {
        if (!ExpiresTimeSpanValue.IsValid())
        {
            return nullptr;
        }
        return ExpiresTimeSpanValue;
    }

    TOptional<int64> FCreateGlobalMessageMasterRequest::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FCreateGlobalMessageMasterRequest::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateGlobalMessageMasterRequest>()
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
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
             }() : nullptr)
          ->WithExpiresTimeSpan(Data->HasField("expiresTimeSpan") ? [Data]() -> Model::FTimeSpanPtr
              {
                  if (Data->HasTypedField<EJson::Null>("expiresTimeSpan"))
                  {
                      return nullptr;
                  }
                  return Model::FTimeSpan::FromJson(Data->GetObjectField("expiresTimeSpan"));
             }() : nullptr)
            ->WithExpiresAt(Data->HasField("expiresAt") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("expiresAt", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FCreateGlobalMessageMasterRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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
        if (ExpiresTimeSpanValue != nullptr && ExpiresTimeSpanValue.IsValid())
        {
            JsonRootObject->SetObjectField("expiresTimeSpan", ExpiresTimeSpanValue->ToJson());
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        return JsonRootObject;
    }
}