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
    class GS2GRADE_API FDefaultGradeModel final : public Gs2Object, public TSharedFromThis<FDefaultGradeModel>
    {
        TOptional<FString> PropertyIdRegexValue;
        TOptional<int64> DefaultGradeValueValue;

    public:
        FDefaultGradeModel();
        FDefaultGradeModel(
            const FDefaultGradeModel& From
        );
        virtual ~FDefaultGradeModel() override = default;

        TSharedPtr<FDefaultGradeModel> WithPropertyIdRegex(const TOptional<FString> PropertyIdRegex);
        TSharedPtr<FDefaultGradeModel> WithDefaultGradeValue(const TOptional<int64> DefaultGradeValue);

        TOptional<FString> GetPropertyIdRegex() const;
        TOptional<int64> GetDefaultGradeValue() const;
        FString GetDefaultGradeValueString() const;


        static TSharedPtr<FDefaultGradeModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDefaultGradeModel, ESPMode::ThreadSafe> FDefaultGradeModelPtr;
}