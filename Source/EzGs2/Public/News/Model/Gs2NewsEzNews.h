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
#include "News/Model/News.h"

namespace Gs2::UE5::News::Model
{
	class EZGS2_API FEzNews final : public TSharedFromThis<FEzNews>
	{
        TOptional<FString> SectionValue;
        TOptional<FString> ContentValue;
        TOptional<FString> TitleValue;
        TOptional<FString> ScheduleEventIdValue;
        TOptional<int64> TimestampValue;
        TOptional<FString> FrontMatterValue;

	public:
        TSharedPtr<FEzNews> WithSection(const TOptional<FString> Section);
        TSharedPtr<FEzNews> WithContent(const TOptional<FString> Content);
        TSharedPtr<FEzNews> WithTitle(const TOptional<FString> Title);
        TSharedPtr<FEzNews> WithScheduleEventId(const TOptional<FString> ScheduleEventId);
        TSharedPtr<FEzNews> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FEzNews> WithFrontMatter(const TOptional<FString> FrontMatter);

        TOptional<FString> GetSection() const;

        TOptional<FString> GetContent() const;

        TOptional<FString> GetTitle() const;

        TOptional<FString> GetScheduleEventId() const;

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;

        TOptional<FString> GetFrontMatter() const;

        Gs2::News::Model::FNewsPtr ToModel() const;
        static TSharedPtr<FEzNews> FromModel(Gs2::News::Model::FNewsPtr Model);
    };
    typedef TSharedPtr<FEzNews> FEzNewsPtr;
}