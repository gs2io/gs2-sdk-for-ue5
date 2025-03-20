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
#include "Core/Gs2Object.h"

namespace Gs2::News::Model
{
    class GS2NEWS_API FContent final : public FGs2Object, public TSharedFromThis<FContent>
    {
        TOptional<FString> SectionValue;
        TOptional<FString> ContentValue;
        TOptional<FString> FrontMatterValue;

    public:
        FContent();
        FContent(
            const FContent& From
        );
        virtual ~FContent() override = default;

        TSharedPtr<FContent> WithSection(const TOptional<FString> Section);
        TSharedPtr<FContent> WithContent(const TOptional<FString> Content);
        TSharedPtr<FContent> WithFrontMatter(const TOptional<FString> FrontMatter);

        TOptional<FString> GetSection() const;
        TOptional<FString> GetContent() const;
        TOptional<FString> GetFrontMatter() const;


        static TSharedPtr<FContent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FContent, ESPMode::ThreadSafe> FContentPtr;
}