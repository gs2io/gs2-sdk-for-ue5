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

namespace Gs2::Grade::Model
{
    class GS2GRADE_API FGradeEntryModel final : public FGs2Object, public TSharedFromThis<FGradeEntryModel>
    {
        TOptional<FString> MetadataValue;
        TOptional<int64> RankCapValueValue;
        TOptional<FString> PropertyIdRegexValue;
        TOptional<FString> GradeUpPropertyIdRegexValue;

    public:
        FGradeEntryModel();
        FGradeEntryModel(
            const FGradeEntryModel& From
        );
        virtual ~FGradeEntryModel() override = default;

        TSharedPtr<FGradeEntryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGradeEntryModel> WithRankCapValue(const TOptional<int64> RankCapValue);
        TSharedPtr<FGradeEntryModel> WithPropertyIdRegex(const TOptional<FString> PropertyIdRegex);
        TSharedPtr<FGradeEntryModel> WithGradeUpPropertyIdRegex(const TOptional<FString> GradeUpPropertyIdRegex);

        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;
        TOptional<FString> GetPropertyIdRegex() const;
        TOptional<FString> GetGradeUpPropertyIdRegex() const;


        static TSharedPtr<FGradeEntryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGradeEntryModel, ESPMode::ThreadSafe> FGradeEntryModelPtr;
}