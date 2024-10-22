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

#include "Script/Request/UpdateScriptRequest.h"

namespace Gs2::Script::Request
{
    FUpdateScriptRequest::FUpdateScriptRequest():
        NamespaceNameValue(TOptional<FString>()),
        ScriptNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ScriptValue(TOptional<FString>()),
        DisableStringNumberToNumberValue(TOptional<bool>())
    {
    }

    FUpdateScriptRequest::FUpdateScriptRequest(
        const FUpdateScriptRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ScriptNameValue(From.ScriptNameValue),
        DescriptionValue(From.DescriptionValue),
        ScriptValue(From.ScriptValue),
        DisableStringNumberToNumberValue(From.DisableStringNumberToNumberValue)
    {
    }

    TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequest::WithScriptName(
        const TOptional<FString> ScriptName
    )
    {
        this->ScriptNameValue = ScriptName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequest::WithScript(
        const TOptional<FString> Script
    )
    {
        this->ScriptValue = Script;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequest::WithDisableStringNumberToNumber(
        const TOptional<bool> DisableStringNumberToNumber
    )
    {
        this->DisableStringNumberToNumberValue = DisableStringNumberToNumber;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateScriptRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateScriptRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateScriptRequest::GetScriptName() const
    {
        return ScriptNameValue;
    }

    TOptional<FString> FUpdateScriptRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateScriptRequest::GetScript() const
    {
        return ScriptValue;
    }

    TOptional<bool> FUpdateScriptRequest::GetDisableStringNumberToNumber() const
    {
        return DisableStringNumberToNumberValue;
    }

    FString FUpdateScriptRequest::GetDisableStringNumberToNumberString() const
    {
        if (!DisableStringNumberToNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString(DisableStringNumberToNumberValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FUpdateScriptRequest> FUpdateScriptRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateScriptRequest>()
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
            ->WithScriptName(Data->HasField(ANSI_TO_TCHAR("scriptName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scriptName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScript(Data->HasField(ANSI_TO_TCHAR("script")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("script"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDisableStringNumberToNumber(Data->HasField(ANSI_TO_TCHAR("disableStringNumberToNumber")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("disableStringNumberToNumber"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FUpdateScriptRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (ScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("script", ScriptValue.GetValue());
        }
        if (DisableStringNumberToNumberValue.IsSet())
        {
            JsonRootObject->SetBoolField("disableStringNumberToNumber", DisableStringNumberToNumberValue.GetValue());
        }
        return JsonRootObject;
    }
}