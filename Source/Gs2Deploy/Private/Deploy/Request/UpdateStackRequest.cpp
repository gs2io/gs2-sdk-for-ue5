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

#include "Deploy/Request/UpdateStackRequest.h"

namespace Gs2::Deploy::Request
{
    FUpdateStackRequest::FUpdateStackRequest():
        StackNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TemplateValue(TOptional<FString>())
    {
    }

    FUpdateStackRequest::FUpdateStackRequest(
        const FUpdateStackRequest& From
    ):
        StackNameValue(From.StackNameValue),
        DescriptionValue(From.DescriptionValue),
        TemplateValue(From.TemplateValue)
    {
    }

    TSharedPtr<FUpdateStackRequest> FUpdateStackRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStackRequest> FUpdateStackRequest::WithStackName(
        const TOptional<FString> StackName
    )
    {
        this->StackNameValue = StackName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStackRequest> FUpdateStackRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStackRequest> FUpdateStackRequest::WithTemplate(
        const TOptional<FString> Template
    )
    {
        this->TemplateValue = Template;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateStackRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateStackRequest::GetStackName() const
    {
        return StackNameValue;
    }

    TOptional<FString> FUpdateStackRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateStackRequest::GetTemplate() const
    {
        return TemplateValue;
    }

    TSharedPtr<FUpdateStackRequest> FUpdateStackRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateStackRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithStackName(Data->HasField("stackName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("stackName", v))
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
            ->WithTemplate(Data->HasField("template") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("template", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateStackRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (TemplateValue.IsSet())
        {
            JsonRootObject->SetStringField("template", TemplateValue.GetValue());
        }
        return JsonRootObject;
    }
}