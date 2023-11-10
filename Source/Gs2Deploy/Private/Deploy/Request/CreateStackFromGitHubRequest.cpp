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

#include "Deploy/Request/CreateStackFromGitHubRequest.h"

namespace Gs2::Deploy::Request
{
    FCreateStackFromGitHubRequest::FCreateStackFromGitHubRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        CheckoutSettingValue(nullptr)
    {
    }

    FCreateStackFromGitHubRequest::FCreateStackFromGitHubRequest(
        const FCreateStackFromGitHubRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        CheckoutSettingValue(From.CheckoutSettingValue)
    {
    }

    TSharedPtr<FCreateStackFromGitHubRequest> FCreateStackFromGitHubRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStackFromGitHubRequest> FCreateStackFromGitHubRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStackFromGitHubRequest> FCreateStackFromGitHubRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStackFromGitHubRequest> FCreateStackFromGitHubRequest::WithCheckoutSetting(
        const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting
    )
    {
        this->CheckoutSettingValue = CheckoutSetting;
        return SharedThis(this);
    }

    TOptional<FString> FCreateStackFromGitHubRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateStackFromGitHubRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateStackFromGitHubRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TSharedPtr<Model::FGitHubCheckoutSetting> FCreateStackFromGitHubRequest::GetCheckoutSetting() const
    {
        if (!CheckoutSettingValue.IsValid())
        {
            return nullptr;
        }
        return CheckoutSettingValue;
    }

    TSharedPtr<FCreateStackFromGitHubRequest> FCreateStackFromGitHubRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateStackFromGitHubRequest>()
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
          ->WithCheckoutSetting(Data->HasField("checkoutSetting") ? [Data]() -> Model::FGitHubCheckoutSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("checkoutSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FGitHubCheckoutSetting::FromJson(Data->GetObjectField("checkoutSetting"));
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateStackFromGitHubRequest::ToJson() const
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
        if (CheckoutSettingValue != nullptr && CheckoutSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("checkoutSetting", CheckoutSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}