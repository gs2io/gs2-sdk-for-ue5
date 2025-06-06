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

#include "Freeze/Request/GetOutputRequest.h"

namespace Gs2::Freeze::Request
{
    FGetOutputRequest::FGetOutputRequest():
        StageNameValue(TOptional<FString>()),
        OutputNameValue(TOptional<FString>())
    {
    }

    FGetOutputRequest::FGetOutputRequest(
        const FGetOutputRequest& From
    ):
        StageNameValue(From.StageNameValue),
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

    TSharedPtr<FGetOutputRequest> FGetOutputRequest::WithStageName(
        const TOptional<FString> StageName
    )
    {
        this->StageNameValue = StageName;
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

    TOptional<FString> FGetOutputRequest::GetStageName() const
    {
        return StageNameValue;
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
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithStageName(Data->HasField(ANSI_TO_TCHAR("stageName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stageName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithOutputName(Data->HasField(ANSI_TO_TCHAR("outputName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("outputName"), v))
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
        if (StageNameValue.IsSet())
        {
            JsonRootObject->SetStringField("stageName", StageNameValue.GetValue());
        }
        if (OutputNameValue.IsSet())
        {
            JsonRootObject->SetStringField("outputName", OutputNameValue.GetValue());
        }
        return JsonRootObject;
    }
}