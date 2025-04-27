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

#include "Deploy/Request/ChangeSetRequest.h"

namespace Gs2::Deploy::Request
{
    FChangeSetRequest::FChangeSetRequest():
        StackNameValue(TOptional<FString>()),
        ModeValue(TOptional<FString>()),
        TemplateValue(TOptional<FString>()),
        UploadTokenValue(TOptional<FString>())
    {
    }

    FChangeSetRequest::FChangeSetRequest(
        const FChangeSetRequest& From
    ):
        StackNameValue(From.StackNameValue),
        ModeValue(From.ModeValue),
        TemplateValue(From.TemplateValue),
        UploadTokenValue(From.UploadTokenValue)
    {
    }

    TSharedPtr<FChangeSetRequest> FChangeSetRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FChangeSetRequest> FChangeSetRequest::WithStackName(
        const TOptional<FString> StackName
    )
    {
        this->StackNameValue = StackName;
        return SharedThis(this);
    }

    TSharedPtr<FChangeSetRequest> FChangeSetRequest::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FChangeSetRequest> FChangeSetRequest::WithTemplate(
        const TOptional<FString> Template
    )
    {
        this->TemplateValue = Template;
        return SharedThis(this);
    }

    TSharedPtr<FChangeSetRequest> FChangeSetRequest::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TOptional<FString> FChangeSetRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FChangeSetRequest::GetStackName() const
    {
        return StackNameValue;
    }

    TOptional<FString> FChangeSetRequest::GetMode() const
    {
        return ModeValue;
    }

    TOptional<FString> FChangeSetRequest::GetTemplate() const
    {
        return TemplateValue;
    }

    TOptional<FString> FChangeSetRequest::GetUploadToken() const
    {
        return UploadTokenValue;
    }

    TSharedPtr<FChangeSetRequest> FChangeSetRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FChangeSetRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithStackName(Data->HasField(ANSI_TO_TCHAR("stackName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stackName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMode(Data->HasField(ANSI_TO_TCHAR("mode")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("mode"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTemplate(Data->HasField(ANSI_TO_TCHAR("template")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("template"), v))
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FChangeSetRequest::ToJson() const
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
        if (ModeValue.IsSet())
        {
            JsonRootObject->SetStringField("mode", ModeValue.GetValue());
        }
        if (TemplateValue.IsSet())
        {
            JsonRootObject->SetStringField("template", TemplateValue.GetValue());
        }
        if (UploadTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadToken", UploadTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}