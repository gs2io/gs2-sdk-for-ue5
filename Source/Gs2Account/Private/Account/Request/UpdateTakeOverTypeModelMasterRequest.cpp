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

#include "Account/Request/UpdateTakeOverTypeModelMasterRequest.h"

namespace Gs2::Account::Request
{
    FUpdateTakeOverTypeModelMasterRequest::FUpdateTakeOverTypeModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        TypeValue(TOptional<int32>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        OpenIdConnectSettingValue(nullptr)
    {
    }

    FUpdateTakeOverTypeModelMasterRequest::FUpdateTakeOverTypeModelMasterRequest(
        const FUpdateTakeOverTypeModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        TypeValue(From.TypeValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        OpenIdConnectSettingValue(From.OpenIdConnectSettingValue)
    {
    }

    TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FUpdateTakeOverTypeModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FUpdateTakeOverTypeModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FUpdateTakeOverTypeModelMasterRequest::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FUpdateTakeOverTypeModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FUpdateTakeOverTypeModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FUpdateTakeOverTypeModelMasterRequest::WithOpenIdConnectSetting(
        const TSharedPtr<Model::FOpenIdConnectSetting> OpenIdConnectSetting
    )
    {
        this->OpenIdConnectSettingValue = OpenIdConnectSetting;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateTakeOverTypeModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateTakeOverTypeModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int32> FUpdateTakeOverTypeModelMasterRequest::GetType() const
    {
        return TypeValue;
    }

    FString FUpdateTakeOverTypeModelMasterRequest::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }

    TOptional<FString> FUpdateTakeOverTypeModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateTakeOverTypeModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<Model::FOpenIdConnectSetting> FUpdateTakeOverTypeModelMasterRequest::GetOpenIdConnectSetting() const
    {
        if (!OpenIdConnectSettingValue.IsValid())
        {
            return nullptr;
        }
        return OpenIdConnectSettingValue;
    }

    TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FUpdateTakeOverTypeModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateTakeOverTypeModelMasterRequest>()
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
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("type"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
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
          ->WithOpenIdConnectSetting(Data->HasField(ANSI_TO_TCHAR("openIdConnectSetting")) ? [Data]() -> Model::FOpenIdConnectSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("openIdConnectSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FOpenIdConnectSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("openIdConnectSetting")));
              }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateTakeOverTypeModelMasterRequest::ToJson() const
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
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetNumberField("type", TypeValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (OpenIdConnectSettingValue != nullptr && OpenIdConnectSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("openIdConnectSetting", OpenIdConnectSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}