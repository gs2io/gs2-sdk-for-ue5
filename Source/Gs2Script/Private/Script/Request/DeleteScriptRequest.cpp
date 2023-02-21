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

#include "Script/Request/DeleteScriptRequest.h"

namespace Gs2::Script::Request
{
    FDeleteScriptRequest::FDeleteScriptRequest():
        NamespaceNameValue(TOptional<FString>()),
        ScriptNameValue(TOptional<FString>())
    {
    }

    FDeleteScriptRequest::FDeleteScriptRequest(
        const FDeleteScriptRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ScriptNameValue(From.ScriptNameValue)
    {
    }

    TSharedPtr<FDeleteScriptRequest> FDeleteScriptRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteScriptRequest> FDeleteScriptRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteScriptRequest> FDeleteScriptRequest::WithScriptName(
        const TOptional<FString> ScriptName
    )
    {
        this->ScriptNameValue = ScriptName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteScriptRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteScriptRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteScriptRequest::GetScriptName() const
    {
        return ScriptNameValue;
    }

    TSharedPtr<FDeleteScriptRequest> FDeleteScriptRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteScriptRequest>()
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
            ->WithScriptName(Data->HasField("scriptName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("scriptName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteScriptRequest::ToJson() const
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
        if (ScriptNameValue.IsSet())
        {
            JsonRootObject->SetStringField("scriptName", ScriptNameValue.GetValue());
        }
        return JsonRootObject;
    }
}