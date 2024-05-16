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

#include "Inbox/Request/UpdateGlobalMessageMasterRequest.h"

namespace Gs2::Inbox::Request
{
    FUpdateGlobalMessageMasterRequest::FUpdateGlobalMessageMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        GlobalMessageNameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReadAcquireActionsValue(nullptr),
        ExpiresTimeSpanValue(nullptr),
        ExpiresAtValue(TOptional<int64>())
    {
    }

    FUpdateGlobalMessageMasterRequest::FUpdateGlobalMessageMasterRequest(
        const FUpdateGlobalMessageMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GlobalMessageNameValue(From.GlobalMessageNameValue),
        MetadataValue(From.MetadataValue),
        ReadAcquireActionsValue(From.ReadAcquireActionsValue),
        ExpiresTimeSpanValue(From.ExpiresTimeSpanValue),
        ExpiresAtValue(From.ExpiresAtValue)
    {
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::WithGlobalMessageName(
        const TOptional<FString> GlobalMessageName
    )
    {
        this->GlobalMessageNameValue = GlobalMessageName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::WithReadAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions
    )
    {
        this->ReadAcquireActionsValue = ReadAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::WithExpiresTimeSpan(
        const TSharedPtr<Model::FTimeSpan> ExpiresTimeSpan
    )
    {
        this->ExpiresTimeSpanValue = ExpiresTimeSpan;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateGlobalMessageMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateGlobalMessageMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateGlobalMessageMasterRequest::GetGlobalMessageName() const
    {
        return GlobalMessageNameValue;
    }

    TOptional<FString> FUpdateGlobalMessageMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FUpdateGlobalMessageMasterRequest::GetReadAcquireActions() const
    {
        if (!ReadAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return ReadAcquireActionsValue;
    }

    TSharedPtr<Model::FTimeSpan> FUpdateGlobalMessageMasterRequest::GetExpiresTimeSpan() const
    {
        if (!ExpiresTimeSpanValue.IsValid())
        {
            return nullptr;
        }
        return ExpiresTimeSpanValue;
    }

    TOptional<int64> FUpdateGlobalMessageMasterRequest::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FUpdateGlobalMessageMasterRequest::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    TSharedPtr<FUpdateGlobalMessageMasterRequest> FUpdateGlobalMessageMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateGlobalMessageMasterRequest>()
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
            ->WithGlobalMessageName(Data->HasField(ANSI_TO_TCHAR("globalMessageName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("globalMessageName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithReadAcquireActions(Data->HasField(ANSI_TO_TCHAR("readAcquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("readAcquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("readAcquireActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("readAcquireActions")))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
          ->WithExpiresTimeSpan(Data->HasField(ANSI_TO_TCHAR("expiresTimeSpan")) ? [Data]() -> Model::FTimeSpanPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("expiresTimeSpan")))
                  {
                      return nullptr;
                  }
                  return Model::FTimeSpan::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("expiresTimeSpan")));
              }() : nullptr)
            ->WithExpiresAt(Data->HasField(ANSI_TO_TCHAR("expiresAt")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expiresAt"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FUpdateGlobalMessageMasterRequest::ToJson() const
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
        if (GlobalMessageNameValue.IsSet())
        {
            JsonRootObject->SetStringField("globalMessageName", GlobalMessageNameValue.GetValue());
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