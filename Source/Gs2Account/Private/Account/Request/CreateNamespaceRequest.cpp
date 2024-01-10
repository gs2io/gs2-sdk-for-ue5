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

#include "Account/Request/CreateNamespaceRequest.h"

namespace Gs2::Account::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ChangePasswordIfTakeOverValue(TOptional<bool>()),
        DifferentUserIdForLoginAndDataRetentionValue(TOptional<bool>()),
        CreateAccountScriptValue(nullptr),
        AuthenticationScriptValue(nullptr),
        CreateTakeOverScriptValue(nullptr),
        DoTakeOverScriptValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        ChangePasswordIfTakeOverValue(From.ChangePasswordIfTakeOverValue),
        DifferentUserIdForLoginAndDataRetentionValue(From.DifferentUserIdForLoginAndDataRetentionValue),
        CreateAccountScriptValue(From.CreateAccountScriptValue),
        AuthenticationScriptValue(From.AuthenticationScriptValue),
        CreateTakeOverScriptValue(From.CreateTakeOverScriptValue),
        DoTakeOverScriptValue(From.DoTakeOverScriptValue),
        LogSettingValue(From.LogSettingValue)
    {
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangePasswordIfTakeOver(
        const TOptional<bool> ChangePasswordIfTakeOver
    )
    {
        this->ChangePasswordIfTakeOverValue = ChangePasswordIfTakeOver;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDifferentUserIdForLoginAndDataRetention(
        const TOptional<bool> DifferentUserIdForLoginAndDataRetention
    )
    {
        this->DifferentUserIdForLoginAndDataRetentionValue = DifferentUserIdForLoginAndDataRetention;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCreateAccountScript(
        const TSharedPtr<Model::FScriptSetting> CreateAccountScript
    )
    {
        this->CreateAccountScriptValue = CreateAccountScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAuthenticationScript(
        const TSharedPtr<Model::FScriptSetting> AuthenticationScript
    )
    {
        this->AuthenticationScriptValue = AuthenticationScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCreateTakeOverScript(
        const TSharedPtr<Model::FScriptSetting> CreateTakeOverScript
    )
    {
        this->CreateTakeOverScriptValue = CreateTakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDoTakeOverScript(
        const TSharedPtr<Model::FScriptSetting> DoTakeOverScript
    )
    {
        this->DoTakeOverScriptValue = DoTakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithLogSetting(
        const TSharedPtr<Model::FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TOptional<FString> FCreateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<bool> FCreateNamespaceRequest::GetChangePasswordIfTakeOver() const
    {
        return ChangePasswordIfTakeOverValue;
    }

    FString FCreateNamespaceRequest::GetChangePasswordIfTakeOverString() const
    {
        if (!ChangePasswordIfTakeOverValue.IsSet())
        {
            return FString("null");
        }
        return FString(ChangePasswordIfTakeOverValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FCreateNamespaceRequest::GetDifferentUserIdForLoginAndDataRetention() const
    {
        return DifferentUserIdForLoginAndDataRetentionValue;
    }

    FString FCreateNamespaceRequest::GetDifferentUserIdForLoginAndDataRetentionString() const
    {
        if (!DifferentUserIdForLoginAndDataRetentionValue.IsSet())
        {
            return FString("null");
        }
        return FString(DifferentUserIdForLoginAndDataRetentionValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetCreateAccountScript() const
    {
        if (!CreateAccountScriptValue.IsValid())
        {
            return nullptr;
        }
        return CreateAccountScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetAuthenticationScript() const
    {
        if (!AuthenticationScriptValue.IsValid())
        {
            return nullptr;
        }
        return AuthenticationScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetCreateTakeOverScript() const
    {
        if (!CreateTakeOverScriptValue.IsValid())
        {
            return nullptr;
        }
        return CreateTakeOverScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetDoTakeOverScript() const
    {
        if (!DoTakeOverScriptValue.IsValid())
        {
            return nullptr;
        }
        return DoTakeOverScriptValue;
    }

    TSharedPtr<Model::FLogSetting> FCreateNamespaceRequest::GetLogSetting() const
    {
        if (!LogSettingValue.IsValid())
        {
            return nullptr;
        }
        return LogSettingValue;
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateNamespaceRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithChangePasswordIfTakeOver(Data->HasField("changePasswordIfTakeOver") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("changePasswordIfTakeOver", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithDifferentUserIdForLoginAndDataRetention(Data->HasField("differentUserIdForLoginAndDataRetention") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("differentUserIdForLoginAndDataRetention", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithCreateAccountScript(Data->HasField("createAccountScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("createAccountScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("createAccountScript"));
              }() : nullptr)
          ->WithAuthenticationScript(Data->HasField("authenticationScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("authenticationScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("authenticationScript"));
              }() : nullptr)
          ->WithCreateTakeOverScript(Data->HasField("createTakeOverScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("createTakeOverScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("createTakeOverScript"));
              }() : nullptr)
          ->WithDoTakeOverScript(Data->HasField("doTakeOverScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("doTakeOverScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("doTakeOverScript"));
              }() : nullptr)
          ->WithLogSetting(Data->HasField("logSetting") ? [Data]() -> Model::FLogSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("logSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FLogSetting::FromJson(Data->GetObjectField("logSetting"));
              }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (ChangePasswordIfTakeOverValue.IsSet())
        {
            JsonRootObject->SetBoolField("changePasswordIfTakeOver", ChangePasswordIfTakeOverValue.GetValue());
        }
        if (DifferentUserIdForLoginAndDataRetentionValue.IsSet())
        {
            JsonRootObject->SetBoolField("differentUserIdForLoginAndDataRetention", DifferentUserIdForLoginAndDataRetentionValue.GetValue());
        }
        if (CreateAccountScriptValue != nullptr && CreateAccountScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createAccountScript", CreateAccountScriptValue->ToJson());
        }
        if (AuthenticationScriptValue != nullptr && AuthenticationScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("authenticationScript", AuthenticationScriptValue->ToJson());
        }
        if (CreateTakeOverScriptValue != nullptr && CreateTakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createTakeOverScript", CreateTakeOverScriptValue->ToJson());
        }
        if (DoTakeOverScriptValue != nullptr && DoTakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("doTakeOverScript", DoTakeOverScriptValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}