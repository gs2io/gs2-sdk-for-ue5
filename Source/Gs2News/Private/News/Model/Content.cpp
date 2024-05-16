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

#include "News/Model/Content.h"

namespace Gs2::News::Model
{
    FContent::FContent():
        SectionValue(TOptional<FString>()),
        ContentValue(TOptional<FString>()),
        FrontMatterValue(TOptional<FString>())
    {
    }

    FContent::FContent(
        const FContent& From
    ):
        SectionValue(From.SectionValue),
        ContentValue(From.ContentValue),
        FrontMatterValue(From.FrontMatterValue)
    {
    }

    TSharedPtr<FContent> FContent::WithSection(
        const TOptional<FString> Section
    )
    {
        this->SectionValue = Section;
        return SharedThis(this);
    }

    TSharedPtr<FContent> FContent::WithContent(
        const TOptional<FString> Content
    )
    {
        this->ContentValue = Content;
        return SharedThis(this);
    }

    TSharedPtr<FContent> FContent::WithFrontMatter(
        const TOptional<FString> FrontMatter
    )
    {
        this->FrontMatterValue = FrontMatter;
        return SharedThis(this);
    }
    TOptional<FString> FContent::GetSection() const
    {
        return SectionValue;
    }
    TOptional<FString> FContent::GetContent() const
    {
        return ContentValue;
    }
    TOptional<FString> FContent::GetFrontMatter() const
    {
        return FrontMatterValue;
    }

    TSharedPtr<FContent> FContent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FContent>()
            ->WithSection(Data->HasField(ANSI_TO_TCHAR("section")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("section"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithContent(Data->HasField(ANSI_TO_TCHAR("content")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("content"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithFrontMatter(Data->HasField(ANSI_TO_TCHAR("frontMatter")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("frontMatter"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FContent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SectionValue.IsSet())
        {
            JsonRootObject->SetStringField("section", SectionValue.GetValue());
        }
        if (ContentValue.IsSet())
        {
            JsonRootObject->SetStringField("content", ContentValue.GetValue());
        }
        if (FrontMatterValue.IsSet())
        {
            JsonRootObject->SetStringField("frontMatter", FrontMatterValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FContent::TypeName = "Content";
}