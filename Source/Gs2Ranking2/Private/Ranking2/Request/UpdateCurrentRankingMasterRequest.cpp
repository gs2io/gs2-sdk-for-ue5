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

#include "Ranking2/Request/UpdateCurrentRankingMasterRequest.h"

namespace Gs2::Ranking2::Request
{
    FUpdateCurrentRankingMasterRequest::FUpdateCurrentRankingMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        SettingsValue(TOptional<FString>())
    {
    }

    FUpdateCurrentRankingMasterRequest::FUpdateCurrentRankingMasterRequest(
        const FUpdateCurrentRankingMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SettingsValue(From.SettingsValue)
    {
    }

    TSharedPtr<FUpdateCurrentRankingMasterRequest> FUpdateCurrentRankingMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentRankingMasterRequest> FUpdateCurrentRankingMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentRankingMasterRequest> FUpdateCurrentRankingMasterRequest::WithSettings(
        const TOptional<FString> Settings
    )
    {
        this->SettingsValue = Settings;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCurrentRankingMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCurrentRankingMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateCurrentRankingMasterRequest::GetSettings() const
    {
        return SettingsValue;
    }

    TSharedPtr<FUpdateCurrentRankingMasterRequest> FUpdateCurrentRankingMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCurrentRankingMasterRequest>()
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
            ->WithSettings(Data->HasField(ANSI_TO_TCHAR("settings")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("settings"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateCurrentRankingMasterRequest::ToJson() const
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