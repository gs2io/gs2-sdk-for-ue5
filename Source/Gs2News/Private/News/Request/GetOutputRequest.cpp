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

#include "News/Request/GetOutputRequest.h"

namespace Gs2::News::Request
{
    FGetOutputRequest::FGetOutputRequest():
        NamespaceNameValue(TOptional<FString>()),
        UploadTokenValue(TOptional<FString>()),
        OutputNameValue(TOptional<FString>())
    {
    }

    FGetOutputRequest::FGetOutputRequest(
        const FGetOutputRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UploadTokenValue(From.UploadTokenValue),
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

    TSharedPtr<FGetOutputRequest> FGetOutputRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetOutputRequest> FGetOutputRequest::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
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

    TOptional<FString> FGetOutputRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetOutputRequest::GetUploadToken() const
    {
        return UploadTokenValue;
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
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUploadToken(Data->HasField(ANSI_TO_TCHAR("uploadToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("uploadToken"), v))
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
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (UploadTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadToken", UploadTokenValue.GetValue());
        }
        if (OutputNameValue.IsSet())
        {
            JsonRootObject->SetStringField("outputName", OutputNameValue.GetValue());
        }
        return JsonRootObject;
    }
}