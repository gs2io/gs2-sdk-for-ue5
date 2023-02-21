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
#include "../Model/ExperienceModelMaster.h"

namespace Gs2::Experience::Result
{
    class GS2EXPERIENCE_API FDescribeExperienceModelMastersResult final : public TSharedFromThis<FDescribeExperienceModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FExperienceModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeExperienceModelMastersResult();
        FDescribeExperienceModelMastersResult(
            const FDescribeExperienceModelMastersResult& From
        );
        ~FDescribeExperienceModelMastersResult() = default;

        TSharedPtr<FDescribeExperienceModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FExperienceModelMaster>>> Items);
        TSharedPtr<FDescribeExperienceModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FExperienceModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeExperienceModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeExperienceModelMastersResult, ESPMode::ThreadSafe> FDescribeExperienceModelMastersResultPtr;
}