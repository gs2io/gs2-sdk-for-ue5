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

#include "Script/Request/InvokeScriptRequest.h"

namespace Gs2::Script::Request
{
    FInvokeScriptRequest::FInvokeScriptRequest():
        ScriptIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>())
    {
    }

    FInvokeScriptRequest::FInvokeScriptRequest(
        const FInvokeScriptRequest& From
    ):
        ScriptIdValue(From.ScriptIdValue),
        UserIdValue(From.UserIdValue),
        ArgsValue(From.ArgsValue)
    {
    }

    TSharedPtr<FInvokeScriptRequest> FInvokeScriptRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptRequest> FInvokeScriptRequest::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptRequest> FInvokeScriptRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptRequest> FInvokeScriptRequest::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TOptional<FString> FInvokeScriptRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FInvokeScriptRequest::GetScriptId() const
    {
        return ScriptIdValue;
    }

    TOptional<FString> FInvokeScriptRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FInvokeScriptRequest::GetArgs() const
    {
        return ArgsValue;
    }

    TSharedPtr<FInvokeScriptRequest> FInvokeScriptRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FInvokeScriptRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithScriptId(Data->HasField("scriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("scriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithArgs(Data->HasField("args") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("args", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FInvokeScriptRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (ScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scriptId", ScriptIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ArgsValue.IsSet())
        {
            JsonRootObject->SetStringField("args", ArgsValue.GetValue());
        }
        return JsonRootObject;
    }
}