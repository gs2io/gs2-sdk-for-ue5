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

#include "Enhance/Request/UpdateCurrentRateMasterRequest.h"

namespace Gs2::Enhance::Request
{
    FUpdateCurrentRateMasterRequest::FUpdateCurrentRateMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        SettingsValue(TOptional<FString>())
    {
    }

    FUpdateCurrentRateMasterRequest::FUpdateCurrentRateMasterRequest(
        const FUpdateCurrentRateMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SettingsValue(From.SettingsValue)
    {
    }

    TSharedPtr<FUpdateCurrentRateMasterRequest> FUpdateCurrentRateMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentRateMasterRequest> FUpdateCurrentRateMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentRateMasterRequest> FUpdateCurrentRateMasterRequest::WithSettings(
        const TOptional<FString> Settings
    )
    {
        this->SettingsValue = Settings;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCurrentRateMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCurrentRateMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateCurrentRateMasterRequest::GetSettings() const
    {
        return SettingsValue;
    }

    TSharedPtr<FUpdateCurrentRateMasterRequest> FUpdateCurrentRateMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCurrentRateMasterRequest>()
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
            ->WithSettings(Data->HasField("settings") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("settings", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateCurrentRateMasterRequest::ToJson() const
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
        if (SettingsValue.IsSet())
        {
            JsonRootObject->SetStringField("settings", SettingsValue.GetValue());
        }
        return JsonRootObject;
    }
}