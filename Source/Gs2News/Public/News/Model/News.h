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

#pragma once

#include "CoreMinimal.h"

namespace Gs2::News::Model
{
    class GS2NEWS_API FNews final : public TSharedFromThis<FNews>
    {
        TOptional<FString> SectionValue;
        TOptional<FString> ContentValue;
        TOptional<FString> TitleValue;
        TOptional<FString> ScheduleEventIdValue;
        TOptional<int64> TimestampValue;
        TOptional<FString> FrontMatterValue;

    public:
        FNews();
        FNews(
            const FNews& From
        );
        ~FNews() = default;

        TSharedPtr<FNews> WithSection(const TOptional<FString> Section);
        TSharedPtr<FNews> WithContent(const TOptional<FString> Content);
        TSharedPtr<FNews> WithTitle(const TOptional<FString> Title);
        TSharedPtr<FNews> WithScheduleEventId(const TOptional<FString> ScheduleEventId);
        TSharedPtr<FNews> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FNews> WithFrontMatter(const TOptional<FString> FrontMatter);

        TOptional<FString> GetSection() const;
        TOptional<FString> GetContent() const;
        TOptional<FString> GetTitle() const;
        TOptional<FString> GetScheduleEventId() const;
        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetFrontMatter() const;


        static TSharedPtr<FNews> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNews, ESPMode::ThreadSafe> FNewsPtr;
}