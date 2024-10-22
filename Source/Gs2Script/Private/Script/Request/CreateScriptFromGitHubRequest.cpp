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

#include "Script/Request/CreateScriptFromGitHubRequest.h"

namespace Gs2::Script::Request
{
    FCreateScriptFromGitHubRequest::FCreateScriptFromGitHubRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        CheckoutSettingValue(nullptr),
        DisableStringNumberToNumberValue(TOptional<bool>())
    {
    }

    FCreateScriptFromGitHubRequest::FCreateScriptFromGitHubRequest(
        const FCreateScriptFromGitHubRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        CheckoutSettingValue(From.CheckoutSettingValue),
        DisableStringNumberToNumberValue(From.DisableStringNumberToNumberValue)
    {
    }

    TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequest::WithCheckoutSetting(
        const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting
    )
    {
        this->CheckoutSettingValue = CheckoutSetting;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequest::WithDisableStringNumberToNumber(
        const TOptional<bool> DisableStringNumberToNumber
    )
    {
        this->DisableStringNumberToNumberValue = DisableStringNumberToNumber;
        return SharedThis(this);
    }

    TOptional<FString> FCreateScriptFromGitHubRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateScriptFromGitHubRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateScriptFromGitHubRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateScriptFromGitHubRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TSharedPtr<Model::FGitHubCheckoutSetting> FCreateScriptFromGitHubRequest::GetCheckoutSetting() const
    {
        if (!CheckoutSettingValue.IsValid())
        {
            return nullptr;
        }
        return CheckoutSettingValue;
    }

    TOptional<bool> FCreateScriptFromGitHubRequest::GetDisableStringNumberToNumber() const
    {
        return DisableStringNumberToNumberValue;
    }

    FString FCreateScriptFromGitHubRequest::GetDisableStringNumberToNumberString() const
    {
        if (!DisableStringNumberToNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString(DisableStringNumberToNumberValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateScriptFromGitHubRequest>()
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
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithCheckoutSetting(Data->HasField(ANSI_TO_TCHAR("checkoutSetting")) ? [Data]() -> Model::FGitHubCheckoutSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("checkoutSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FGitHubCheckoutSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("checkoutSetting")));
              }() : nullptr)
            ->WithDisableStringNumberToNumber(Data->HasField(ANSI_TO_TCHAR("disableStringNumberToNumber")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("disableStringNumberToNumber"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FCreateScriptFromGitHubRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (CheckoutSettingValue != nullptr && CheckoutSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("checkoutSetting", CheckoutSettingValue->ToJson());
        }
        if (DisableStringNumberToNumberValue.IsSet())
        {
            JsonRootObject->SetBoolField("disableStringNumberToNumber", DisableStringNumberToNumberValue.GetValue());
        }
        return JsonRootObject;
    }
}