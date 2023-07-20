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

namespace Gs2::Enchant::Model
{
    class GS2ENCHANT_API FRarityParameterCountModel final : public Gs2Object, public TSharedFromThis<FRarityParameterCountModel>
    {
        TOptional<int32> CountValue;
        TOptional<int32> WeightValue;

    public:
        FRarityParameterCountModel();
        FRarityParameterCountModel(
            const FRarityParameterCountModel& From
        );
        virtual ~FRarityParameterCountModel() override = default;

        TSharedPtr<FRarityParameterCountModel> WithCount(const TOptional<int32> Count);
        TSharedPtr<FRarityParameterCountModel> WithWeight(const TOptional<int32> Weight);

        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<int32> GetWeight() const;
        FString GetWeightString() const;


        static TSharedPtr<FRarityParameterCountModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRarityParameterCountModel, ESPMode::ThreadSafe> FRarityParameterCountModelPtr;
}