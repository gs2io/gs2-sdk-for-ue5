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

#include "StateMachine/Request/ExitStateMachineRequest.h"

namespace Gs2::StateMachine::Request
{
    FExitStateMachineRequest::FExitStateMachineRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        StatusNameValue(TOptional<FString>())
    {
    }

    FExitStateMachineRequest::FExitStateMachineRequest(
        const FExitStateMachineRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        StatusNameValue(From.StatusNameValue)
    {
    }

    TSharedPtr<FExitStateMachineRequest> FExitStateMachineRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FExitStateMachineRequest> FExitStateMachineRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FExitStateMachineRequest> FExitStateMachineRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FExitStateMachineRequest> FExitStateMachineRequest::WithStatusName(
        const TOptional<FString> StatusName
    )
    {
        this->StatusNameValue = StatusName;
        return SharedThis(this);
    }

    TSharedPtr<FExitStateMachineRequest> FExitStateMachineRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FExitStateMachineRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FExitStateMachineRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FExitStateMachineRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FExitStateMachineRequest::GetStatusName() const
    {
        return StatusNameValue;
    }

    TOptional<FString> FExitStateMachineRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FExitStateMachineRequest> FExitStateMachineRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FExitStateMachineRequest>()
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
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStatusName(Data->HasField(ANSI_TO_TCHAR("statusName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("statusName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FExitStateMachineRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (StatusNameValue.IsSet())
        {
            JsonRootObject->SetStringField("statusName", StatusNameValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}