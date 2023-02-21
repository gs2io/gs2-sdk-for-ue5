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

#include "Deploy/Request/CreateStackRequest.h"

namespace Gs2::Deploy::Request
{
    FCreateStackRequest::FCreateStackRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TemplateValue(TOptional<FString>())
    {
    }

    FCreateStackRequest::FCreateStackRequest(
        const FCreateStackRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TemplateValue(From.TemplateValue)
    {
    }

    TSharedPtr<FCreateStackRequest> FCreateStackRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStackRequest> FCreateStackRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStackRequest> FCreateStackRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateStackRequest> FCreateStackRequest::WithTemplate(
        const TOptional<FString> Template
    )
    {
        this->TemplateValue = Template;
        return SharedThis(this);
    }

    TOptional<FString> FCreateStackRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateStackRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateStackRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateStackRequest::GetTemplate() const
    {
        return TemplateValue;
    }

    TSharedPtr<FCreateStackRequest> FCreateStackRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateStackRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("name", v))
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

    TSharedPtr<FJsonObject> FCreateStackRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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