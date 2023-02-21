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

#include "Schedule/Request/GetTriggerRequest.h"

namespace Gs2::Schedule::Request
{
    FGetTriggerRequest::FGetTriggerRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TriggerNameValue(TOptional<FString>())
    {
    }

    FGetTriggerRequest::FGetTriggerRequest(
        const FGetTriggerRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        TriggerNameValue(From.TriggerNameValue)
    {
    }

    TSharedPtr<FGetTriggerRequest> FGetTriggerRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetTriggerRequest> FGetTriggerRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetTriggerRequest> FGetTriggerRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetTriggerRequest> FGetTriggerRequest::WithTriggerName(
        const TOptional<FString> TriggerName
    )
    {
        this->TriggerNameValue = TriggerName;
        return SharedThis(this);
    }

    TOptional<FString> FGetTriggerRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetTriggerRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetTriggerRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FGetTriggerRequest::GetTriggerName() const
    {
        return TriggerNameValue;
    }

    TSharedPtr<FGetTriggerRequest> FGetTriggerRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetTriggerRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTriggerName(Data->HasField("triggerName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("triggerName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetTriggerRequest::ToJson() const
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
        if (TriggerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("triggerName", TriggerNameValue.GetValue());
        }
        return JsonRootObject;
    }
}