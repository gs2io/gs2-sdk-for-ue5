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

#include "Matchmaking/Request/UpdateCurrentRatingModelMasterFromGitHubRequest.h"

namespace Gs2::Matchmaking::Request
{
    FUpdateCurrentRatingModelMasterFromGitHubRequest::FUpdateCurrentRatingModelMasterFromGitHubRequest():
        NamespaceNameValue(TOptional<FString>()),
        CheckoutSettingValue(nullptr)
    {
    }

    FUpdateCurrentRatingModelMasterFromGitHubRequest::FUpdateCurrentRatingModelMasterFromGitHubRequest(
        const FUpdateCurrentRatingModelMasterFromGitHubRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CheckoutSettingValue(From.CheckoutSettingValue)
    {
    }

    TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> FUpdateCurrentRatingModelMasterFromGitHubRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> FUpdateCurrentRatingModelMasterFromGitHubRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> FUpdateCurrentRatingModelMasterFromGitHubRequest::WithCheckoutSetting(
        const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting
    )
    {
        this->CheckoutSettingValue = CheckoutSetting;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCurrentRatingModelMasterFromGitHubRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCurrentRatingModelMasterFromGitHubRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<Model::FGitHubCheckoutSetting> FUpdateCurrentRatingModelMasterFromGitHubRequest::GetCheckoutSetting() const
    {
        if (!CheckoutSettingValue.IsValid())
        {
            return nullptr;
        }
        return CheckoutSettingValue;
    }

    TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> FUpdateCurrentRatingModelMasterFromGitHubRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCurrentRatingModelMasterFromGitHubRequest>()
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
          ->WithCheckoutSetting(Data->HasField("checkoutSetting") ? [Data]() -> Model::FGitHubCheckoutSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("checkoutSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FGitHubCheckoutSetting::FromJson(Data->GetObjectField("checkoutSetting"));
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateCurrentRatingModelMasterFromGitHubRequest::ToJson() const
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