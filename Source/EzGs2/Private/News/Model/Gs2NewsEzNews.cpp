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

#include "EzGs2/Public/News/Model/Gs2NewsEzNews.h"

namespace Gs2::UE5::News::Model
{

    TSharedPtr<FEzNews> FEzNews::WithSection(
        const TOptional<FString> Section
    )
    {
        this->SectionValue = Section;
        return SharedThis(this);
    }

    TSharedPtr<FEzNews> FEzNews::WithContent(
        const TOptional<FString> Content
    )
    {
        this->ContentValue = Content;
        return SharedThis(this);
    }

    TSharedPtr<FEzNews> FEzNews::WithTitle(
        const TOptional<FString> Title
    )
    {
        this->TitleValue = Title;
        return SharedThis(this);
    }

    TSharedPtr<FEzNews> FEzNews::WithScheduleEventId(
        const TOptional<FString> ScheduleEventId
    )
    {
        this->ScheduleEventIdValue = ScheduleEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzNews> FEzNews::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FEzNews> FEzNews::WithFrontMatter(
        const TOptional<FString> FrontMatter
    )
    {
        this->FrontMatterValue = FrontMatter;
        return SharedThis(this);
    }
    TOptional<FString> FEzNews::GetSection() const
    {
        return SectionValue;
    }
    TOptional<FString> FEzNews::GetContent() const
    {
        return ContentValue;
    }
    TOptional<FString> FEzNews::GetTitle() const
    {
        return TitleValue;
    }
    TOptional<FString> FEzNews::GetScheduleEventId() const
    {
        return ScheduleEventIdValue;
    }
    TOptional<int64> FEzNews::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FEzNews::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FEzNews::GetFrontMatter() const
    {
        return FrontMatterValue;
    }

    Gs2::News::Model::FNewsPtr FEzNews::ToModel() const
    {
        return MakeShared<Gs2::News::Model::FNews>()
            ->WithSection(SectionValue)
            ->WithContent(ContentValue)
            ->WithTitle(TitleValue)
            ->WithScheduleEventId(ScheduleEventIdValue)
            ->WithTimestamp(TimestampValue)
            ->WithFrontMatter(FrontMatterValue);
    }

    TSharedPtr<FEzNews> FEzNews::FromModel(const Gs2::News::Model::FNewsPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzNews>()
            ->WithSection(Model->GetSection())
            ->WithContent(Model->GetContent())
            ->WithTitle(Model->GetTitle())
            ->WithScheduleEventId(Model->GetScheduleEventId())
            ->WithTimestamp(Model->GetTimestamp())
            ->WithFrontMatter(Model->GetFrontMatter());
    }
}