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

#include "Script/Request/DebugInvokeRequest.h"

namespace Gs2::Script::Request
{
    FDebugInvokeRequest::FDebugInvokeRequest():
        ScriptValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>()),
        RandomStatusValue(nullptr),
        DisableStringNumberToNumberValue(TOptional<bool>())
    {
    }

    FDebugInvokeRequest::FDebugInvokeRequest(
        const FDebugInvokeRequest& From
    ):
        ScriptValue(From.ScriptValue),
        ArgsValue(From.ArgsValue),
        RandomStatusValue(From.RandomStatusValue),
        DisableStringNumberToNumberValue(From.DisableStringNumberToNumberValue)
    {
    }

    TSharedPtr<FDebugInvokeRequest> FDebugInvokeRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeRequest> FDebugInvokeRequest::WithScript(
        const TOptional<FString> Script
    )
    {
        this->ScriptValue = Script;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeRequest> FDebugInvokeRequest::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeRequest> FDebugInvokeRequest::WithRandomStatus(
        const TSharedPtr<Model::FRandomStatus> RandomStatus
    )
    {
        this->RandomStatusValue = RandomStatus;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeRequest> FDebugInvokeRequest::WithDisableStringNumberToNumber(
        const TOptional<bool> DisableStringNumberToNumber
    )
    {
        this->DisableStringNumberToNumberValue = DisableStringNumberToNumber;
        return SharedThis(this);
    }

    TOptional<FString> FDebugInvokeRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDebugInvokeRequest::GetScript() const
    {
        return ScriptValue;
    }

    TOptional<FString> FDebugInvokeRequest::GetArgs() const
    {
        return ArgsValue;
    }

    TSharedPtr<Model::FRandomStatus> FDebugInvokeRequest::GetRandomStatus() const
    {
        if (!RandomStatusValue.IsValid())
        {
            return nullptr;
        }
        return RandomStatusValue;
    }

    TOptional<bool> FDebugInvokeRequest::GetDisableStringNumberToNumber() const
    {
        return DisableStringNumberToNumberValue;
    }

    FString FDebugInvokeRequest::GetDisableStringNumberToNumberString() const
    {
        if (!DisableStringNumberToNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString(DisableStringNumberToNumberValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FDebugInvokeRequest> FDebugInvokeRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDebugInvokeRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithScript(Data->HasField(ANSI_TO_TCHAR("script")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("script"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithArgs(Data->HasField(ANSI_TO_TCHAR("args")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("args"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithRandomStatus(Data->HasField(ANSI_TO_TCHAR("randomStatus")) ? [Data]() -> Model::FRandomStatusPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("randomStatus")))
                  {
                      return nullptr;
                  }
                  return Model::FRandomStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("randomStatus")));
              }() : nullptr)
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

    TSharedPtr<FJsonObject> FDebugInvokeRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (ScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("script", ScriptValue.GetValue());
        }
        if (ArgsValue.IsSet())
        {
            JsonRootObject->SetStringField("args", ArgsValue.GetValue());
        }
        if (RandomStatusValue != nullptr && RandomStatusValue.IsValid())
        {
            JsonRootObject->SetObjectField("randomStatus", RandomStatusValue->ToJson());
        }
        if (DisableStringNumberToNumberValue.IsSet())
        {
            JsonRootObject->SetBoolField("disableStringNumberToNumber", DisableStringNumberToNumberValue.GetValue());
        }
        return JsonRootObject;
    }
}