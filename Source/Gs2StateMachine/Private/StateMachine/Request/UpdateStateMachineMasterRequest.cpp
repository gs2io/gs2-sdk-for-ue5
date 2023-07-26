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

#include "StateMachine/Request/UpdateStateMachineMasterRequest.h"

namespace Gs2::StateMachine::Request
{
    FUpdateStateMachineMasterRequest::FUpdateStateMachineMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        MainStateMachineNameValue(TOptional<FString>()),
        PayloadValue(TOptional<FString>())
    {
    }

    FUpdateStateMachineMasterRequest::FUpdateStateMachineMasterRequest(
        const FUpdateStateMachineMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MainStateMachineNameValue(From.MainStateMachineNameValue),
        PayloadValue(From.PayloadValue)
    {
    }

    TSharedPtr<FUpdateStateMachineMasterRequest> FUpdateStateMachineMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStateMachineMasterRequest> FUpdateStateMachineMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStateMachineMasterRequest> FUpdateStateMachineMasterRequest::WithMainStateMachineName(
        const TOptional<FString> MainStateMachineName
    )
    {
        this->MainStateMachineNameValue = MainStateMachineName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStateMachineMasterRequest> FUpdateStateMachineMasterRequest::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateStateMachineMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateStateMachineMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateStateMachineMasterRequest::GetMainStateMachineName() const
    {
        return MainStateMachineNameValue;
    }

    TOptional<FString> FUpdateStateMachineMasterRequest::GetPayload() const
    {
        return PayloadValue;
    }

    TSharedPtr<FUpdateStateMachineMasterRequest> FUpdateStateMachineMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateStateMachineMasterRequest>()
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
            ->WithMainStateMachineName(Data->HasField("mainStateMachineName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("mainStateMachineName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPayload(Data->HasField("payload") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("payload", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateStateMachineMasterRequest::ToJson() const
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
        if (MainStateMachineNameValue.IsSet())
        {
            JsonRootObject->SetStringField("mainStateMachineName", MainStateMachineNameValue.GetValue());
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("payload", PayloadValue.GetValue());
        }
        return JsonRootObject;
    }
}