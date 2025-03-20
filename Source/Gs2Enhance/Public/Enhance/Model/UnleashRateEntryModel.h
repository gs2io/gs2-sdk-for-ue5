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

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FUnleashRateEntryModel final : public FGs2Object, public TSharedFromThis<FUnleashRateEntryModel>
    {
        TOptional<int64> GradeValueValue;
        TOptional<int32> NeedCountValue;

    public:
        FUnleashRateEntryModel();
        FUnleashRateEntryModel(
            const FUnleashRateEntryModel& From
        );
        virtual ~FUnleashRateEntryModel() override = default;

        TSharedPtr<FUnleashRateEntryModel> WithGradeValue(const TOptional<int64> GradeValue);
        TSharedPtr<FUnleashRateEntryModel> WithNeedCount(const TOptional<int32> NeedCount);

        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;
        TOptional<int32> GetNeedCount() const;
        FString GetNeedCountString() const;


        static TSharedPtr<FUnleashRateEntryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashRateEntryModel, ESPMode::ThreadSafe> FUnleashRateEntryModelPtr;
}