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

#include "Deploy/Request/PreUpdateStackRequest.h"

namespace Gs2::Deploy::Request
{
    FPreUpdateStackRequest::FPreUpdateStackRequest():
        StackNameValue(TOptional<FString>())
    {
    }

    FPreUpdateStackRequest::FPreUpdateStackRequest(
        const FPreUpdateStackRequest& From
    ):
        StackNameValue(From.StackNameValue)
    {
    }

    TSharedPtr<FPreUpdateStackRequest> FPreUpdateStackRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPreUpdateStackRequest> FPreUpdateStackRequest::WithStackName(
        const TOptional<FString> StackName
    )
    {
        this->StackNameValue = StackName;
        return SharedThis(this);
    }

    TOptional<FString> FPreUpdateStackRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPreUpdateStackRequest::GetStackName() const
    {
        return StackNameValue;
    }

    TSharedPtr<FPreUpdateStackRequest> FPreUpdateStackRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPreUpdateStackRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithStackName(Data->HasField(ANSI_TO_TCHAR("stackName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stackName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPreUpdateStackRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (StackNameValue.IsSet())
        {
            JsonRootObject->SetStringField("stackName", StackNameValue.GetValue());
        }
        return JsonRootObject;
    }
}