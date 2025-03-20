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
#include "Content.h"

namespace Gs2::News::Model
{
    class GS2NEWS_API FView final : public FGs2Object, public TSharedFromThis<FView>
    {
        TSharedPtr<TArray<TSharedPtr<FContent>>> ContentsValue;
        TSharedPtr<TArray<TSharedPtr<FContent>>> RemoveContentsValue;

    public:
        FView();
        FView(
            const FView& From
        );
        virtual ~FView() override = default;

        TSharedPtr<FView> WithContents(const TSharedPtr<TArray<TSharedPtr<FContent>>> Contents);
        TSharedPtr<FView> WithRemoveContents(const TSharedPtr<TArray<TSharedPtr<FContent>>> RemoveContents);

        TSharedPtr<TArray<TSharedPtr<FContent>>> GetContents() const;
        TSharedPtr<TArray<TSharedPtr<FContent>>> GetRemoveContents() const;


        static TSharedPtr<FView> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FView, ESPMode::ThreadSafe> FViewPtr;
}