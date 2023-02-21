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

#include "Script/Request/CreateScriptRequest.h"

namespace Gs2::Script::Request
{
    FCreateScriptRequest::FCreateScriptRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ScriptValue(TOptional<FString>())
    {
    }

    FCreateScriptRequest::FCreateScriptRequest(
        const FCreateScriptRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        ScriptValue(From.ScriptValue)
    {
    }

    TSharedPtr<FCreateScriptRequest> FCreateScriptRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptRequest> FCreateScriptRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptRequest> FCreateScriptRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptRequest> FCreateScriptRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateScriptRequest> FCreateScriptRequest::WithScript(
        const TOptional<FString> Script
    )
    {
        this->ScriptValue = Script;
        return SharedThis(this);
    }

    TOptional<FString> FCreateScriptRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateScriptRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateScriptRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateScriptRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateScriptRequest::GetScript() const
    {
        return ScriptValue;
    }

    TSharedPtr<FCreateScriptRequest> FCreateScriptRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateScriptRequest>()
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScript(Data->HasField("script") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("script", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateScriptRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (ScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("script", ScriptValue.GetValue());
        }
        return JsonRootObject;
    }
}