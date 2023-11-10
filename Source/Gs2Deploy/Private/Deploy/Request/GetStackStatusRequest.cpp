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

#include "Deploy/Request/GetStackStatusRequest.h"

namespace Gs2::Deploy::Request
{
    FGetStackStatusRequest::FGetStackStatusRequest():
        StackNameValue(TOptional<FString>())
    {
    }

    FGetStackStatusRequest::FGetStackStatusRequest(
        const FGetStackStatusRequest& From
    ):
        StackNameValue(From.StackNameValue)
    {
    }

    TSharedPtr<FGetStackStatusRequest> FGetStackStatusRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetStackStatusRequest> FGetStackStatusRequest::WithStackName(
        const TOptional<FString> StackName
    )
    {
        this->StackNameValue = StackName;
        return SharedThis(this);
    }

    TOptional<FString> FGetStackStatusRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetStackStatusRequest::GetStackName() const
    {
        return StackNameValue;
    }

    TSharedPtr<FGetStackStatusRequest> FGetStackStatusRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetStackStatusRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithStackName(Data->HasField("stackName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("stackName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetStackStatusRequest::ToJson() const
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