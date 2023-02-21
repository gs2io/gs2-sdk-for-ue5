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

#include "News/Model/News.h"

namespace Gs2::News::Model
{
    FNews::FNews():
        SectionValue(TOptional<FString>()),
        ContentValue(TOptional<FString>()),
        TitleValue(TOptional<FString>()),
        ScheduleEventIdValue(TOptional<FString>()),
        TimestampValue(TOptional<int64>()),
        FrontMatterValue(TOptional<FString>())
    {
    }

    FNews::FNews(
        const FNews& From
    ):
        SectionValue(From.SectionValue),
        ContentValue(From.ContentValue),
        TitleValue(From.TitleValue),
        ScheduleEventIdValue(From.ScheduleEventIdValue),
        TimestampValue(From.TimestampValue),
        FrontMatterValue(From.FrontMatterValue)
    {
    }

    TSharedPtr<FNews> FNews::WithSection(
        const TOptional<FString> Section
    )
    {
        this->SectionValue = Section;
        return SharedThis(this);
    }

    TSharedPtr<FNews> FNews::WithContent(
        const TOptional<FString> Content
    )
    {
        this->ContentValue = Content;
        return SharedThis(this);
    }

    TSharedPtr<FNews> FNews::WithTitle(
        const TOptional<FString> Title
    )
    {
        this->TitleValue = Title;
        return SharedThis(this);
    }

    TSharedPtr<FNews> FNews::WithScheduleEventId(
        const TOptional<FString> ScheduleEventId
    )
    {
        this->ScheduleEventIdValue = ScheduleEventId;
        return SharedThis(this);
    }

    TSharedPtr<FNews> FNews::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FNews> FNews::WithFrontMatter(
        const TOptional<FString> FrontMatter
    )
    {
        this->FrontMatterValue = FrontMatter;
        return SharedThis(this);
    }
    TOptional<FString> FNews::GetSection() const
    {
        return SectionValue;
    }
    TOptional<FString> FNews::GetContent() const
    {
        return ContentValue;
    }
    TOptional<FString> FNews::GetTitle() const
    {
        return TitleValue;
    }
    TOptional<FString> FNews::GetScheduleEventId() const
    {
        return ScheduleEventIdValue;
    }
    TOptional<int64> FNews::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FNews::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FNews::GetFrontMatter() const
    {
        return FrontMatterValue;
    }

    TSharedPtr<FNews> FNews::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNews>()
            ->WithSection(Data->HasField("section") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("section", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithContent(Data->HasField("content") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("content", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTitle(Data->HasField("title") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("title", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScheduleEventId(Data->HasField("scheduleEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scheduleEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTimestamp(Data->HasField("timestamp") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("timestamp", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithFrontMatter(Data->HasField("frontMatter") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("frontMatter", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FNews::ToJson() const
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
        if (TitleValue.IsSet())
        {
            JsonRootObject->SetStringField("title", TitleValue.GetValue());
        }
        if (ScheduleEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scheduleEventId", ScheduleEventIdValue.GetValue());
        }
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (FrontMatterValue.IsSet())
        {
            JsonRootObject->SetStringField("frontMatter", FrontMatterValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FNews::TypeName = "News";
}