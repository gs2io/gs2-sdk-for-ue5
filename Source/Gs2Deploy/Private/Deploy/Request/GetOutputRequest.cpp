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

#include "Deploy/Request/GetOutputRequest.h"

namespace Gs2::Deploy::Request
{
    FGetOutputRequest::FGetOutputRequest():
        StackNameValue(TOptional<FString>()),
        OutputNameValue(TOptional<FString>())
    {
    }

    FGetOutputRequest::FGetOutputRequest(
        const FGetOutputRequest& From
    ):
        StackNameValue(From.StackNameValue),
        OutputNameValue(From.OutputNameValue)
    {
    }

    TSharedPtr<FGetOutputRequest> FGetOutputRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetOutputRequest> FGetOutputRequest::WithStackName(
        const TOptional<FString> StackName
    )
    {
        this->StackNameValue = StackName;
        return SharedThis(this);
    }

    TSharedPtr<FGetOutputRequest> FGetOutputRequest::WithOutputName(
        const TOptional<FString> OutputName
    )
    {
        this->OutputNameValue = OutputName;
        return SharedThis(this);
    }

    TOptional<FString> FGetOutputRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetOutputRequest::GetStackName() const
    {
        return StackNameValue;
    }

    TOptional<FString> FGetOutputRequest::GetOutputName() const
    {
        return OutputNameValue;
    }

    TSharedPtr<FGetOutputRequest> FGetOutputRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetOutputRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithStackName(Data->HasField("stackName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("stackName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithOutputName(Data->HasField("outputName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("outputName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetOutputRequest::ToJson() const
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
        if (OutputNameValue.IsSet())
        {
            JsonRootObject->SetStringField("outputName", OutputNameValue.GetValue());
        }
        return JsonRootObject;
    }
}