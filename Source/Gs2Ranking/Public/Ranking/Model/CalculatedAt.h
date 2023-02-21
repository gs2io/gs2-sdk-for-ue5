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

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FCalculatedAt final : public TSharedFromThis<FCalculatedAt>
    {
        TOptional<FString> CategoryNameValue;
        TOptional<int64> CalculatedAtValue;

    public:
        FCalculatedAt();
        FCalculatedAt(
            const FCalculatedAt& From
        );
        ~FCalculatedAt() = default;

        TSharedPtr<FCalculatedAt> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FCalculatedAt> WithCalculatedAt(const TOptional<int64> CalculatedAt);

        TOptional<FString> GetCategoryName() const;
        TOptional<int64> GetCalculatedAt() const;
        FString GetCalculatedAtString() const;


        static TSharedPtr<FCalculatedAt> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCalculatedAt, ESPMode::ThreadSafe> FCalculatedAtPtr;
}