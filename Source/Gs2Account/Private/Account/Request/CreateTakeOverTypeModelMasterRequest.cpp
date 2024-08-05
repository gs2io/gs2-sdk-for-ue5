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

#include "Account/Request/CreateTakeOverTypeModelMasterRequest.h"

namespace Gs2::Account::Request
{
    FCreateTakeOverTypeModelMasterRequest::FCreateTakeOverTypeModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        TypeValue(TOptional<int32>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        OpenIdConnectSettingValue(nullptr)
    {
    }

    FCreateTakeOverTypeModelMasterRequest::FCreateTakeOverTypeModelMasterRequest(
        const FCreateTakeOverTypeModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        TypeValue(From.TypeValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        OpenIdConnectSettingValue(From.OpenIdConnectSettingValue)
    {
    }

    TSharedPtr<FCreateTakeOverTypeModelMasterRequest> FCreateTakeOverTypeModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverTypeModelMasterRequest> FCreateTakeOverTypeModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverTypeModelMasterRequest> FCreateTakeOverTypeModelMasterRequest::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverTypeModelMasterRequest> FCreateTakeOverTypeModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverTypeModelMasterRequest> FCreateTakeOverTypeModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverTypeModelMasterRequest> FCreateTakeOverTypeModelMasterRequest::WithOpenIdConnectSetting(
        const TSharedPtr<Model::FOpenIdConnectSetting> OpenIdConnectSetting
    )
    {
        this->OpenIdConnectSettingValue = OpenIdConnectSetting;
        return SharedThis(this);
    }

    TOptional<FString> FCreateTakeOverTypeModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateTakeOverTypeModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int32> FCreateTakeOverTypeModelMasterRequest::GetType() const
    {
        return TypeValue;
    }

    FString FCreateTakeOverTypeModelMasterRequest::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }

    TOptional<FString> FCreateTakeOverTypeModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateTakeOverTypeModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<Model::FOpenIdConnectSetting> FCreateTakeOverTypeModelMasterRequest::GetOpenIdConnectSetting() const
    {
        if (!OpenIdConnectSettingValue.IsValid())
        {
            return nullptr;
        }
        return OpenIdConnectSettingValue;
    }

    TSharedPtr<FCreateTakeOverTypeModelMasterRequest> FCreateTakeOverTypeModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateTakeOverTypeModelMasterRequest>()
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

    TSharedPtr<FJsonObject> FCreateTakeOverTypeModelMasterRequest::ToJson() const
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