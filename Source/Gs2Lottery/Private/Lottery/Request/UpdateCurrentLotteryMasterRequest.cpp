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

#include "Lottery/Request/UpdateCurrentLotteryMasterRequest.h"

namespace Gs2::Lottery::Request
{
    FUpdateCurrentLotteryMasterRequest::FUpdateCurrentLotteryMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        SettingsValue(TOptional<FString>())
    {
    }

    FUpdateCurrentLotteryMasterRequest::FUpdateCurrentLotteryMasterRequest(
        const FUpdateCurrentLotteryMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SettingsValue(From.SettingsValue)
    {
    }

    TSharedPtr<FUpdateCurrentLotteryMasterRequest> FUpdateCurrentLotteryMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentLotteryMasterRequest> FUpdateCurrentLotteryMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCurrentLotteryMasterRequest> FUpdateCurrentLotteryMasterRequest::WithSettings(
        const TOptional<FString> Settings
    )
    {
        this->SettingsValue = Settings;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCurrentLotteryMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCurrentLotteryMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateCurrentLotteryMasterRequest::GetSettings() const
    {
        return SettingsValue;
    }

    TSharedPtr<FUpdateCurrentLotteryMasterRequest> FUpdateCurrentLotteryMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCurrentLotteryMasterRequest>()
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

    TSharedPtr<FJsonObject> FUpdateCurrentLotteryMasterRequest::ToJson() const
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