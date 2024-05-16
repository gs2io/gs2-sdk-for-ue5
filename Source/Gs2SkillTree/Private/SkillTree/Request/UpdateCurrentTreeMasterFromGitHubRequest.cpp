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

#include "SkillTree/Request/UpdateCurrentTreeMasterFromGitHubRequest.h"

namespace Gs2::SkillTree::Request
{
    FUpdateCurrentTreeMasterFromGitHubRequest::FUpdateCurrentTreeMasterFromGitHubRequest():
        NamespaceNameValue(TOptional<FString>()),
        CheckoutSettingValue(nullptr)
    {
    }

    FUpdateCurrentTreeMasterFromGitHubRequest::FUpdateCurrentTreeMasterFromGitHubRequest(
        const FUpdateCurrentTreeMasterFromGitHubRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CheckoutSettingValue(From.CheckoutSettingValue)
    {
    }

    TSharedPtr<FUpdateCurrentTreeMasterFromGitHubRequest> FUpdateCurrentTreeMasterFromGitHubRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentTreeMasterFromGitHubRequest> FUpdateCurrentTreeMasterFromGitHubRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentTreeMasterFromGitHubRequest> FUpdateCurrentTreeMasterFromGitHubRequest::WithCheckoutSetting(
        const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting
    )
    {
        this->CheckoutSettingValue = CheckoutSetting;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCurrentTreeMasterFromGitHubRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCurrentTreeMasterFromGitHubRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<Model::FGitHubCheckoutSetting> FUpdateCurrentTreeMasterFromGitHubRequest::GetCheckoutSetting() const
    {
        if (!CheckoutSettingValue.IsValid())
        {
            return nullptr;
        }
        return CheckoutSettingValue;
    }

    TSharedPtr<FUpdateCurrentTreeMasterFromGitHubRequest> FUpdateCurrentTreeMasterFromGitHubRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCurrentTreeMasterFromGitHubRequest>()
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
          ->WithCheckoutSetting(Data->HasField(ANSI_TO_TCHAR("checkoutSetting")) ? [Data]() -> Model::FGitHubCheckoutSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("checkoutSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FGitHubCheckoutSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("checkoutSetting")));
              }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateCurrentTreeMasterFromGitHubRequest::ToJson() const
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
        if (CheckoutSettingValue != nullptr && CheckoutSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("checkoutSetting", CheckoutSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}