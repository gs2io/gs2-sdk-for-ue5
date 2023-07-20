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
    class GS2ENCHANT_API FRarityParameterValueModel final : public Gs2Object, public TSharedFromThis<FRarityParameterValueModel>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ResourceNameValue;
        TOptional<int64> ResourceValueValue;
        TOptional<int32> WeightValue;

    public:
        FRarityParameterValueModel();
        FRarityParameterValueModel(
            const FRarityParameterValueModel& From
        );
        virtual ~FRarityParameterValueModel() override = default;

        TSharedPtr<FRarityParameterValueModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FRarityParameterValueModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRarityParameterValueModel> WithResourceName(const TOptional<FString> ResourceName);
        TSharedPtr<FRarityParameterValueModel> WithResourceValue(const TOptional<int64> ResourceValue);
        TSharedPtr<FRarityParameterValueModel> WithWeight(const TOptional<int32> Weight);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetResourceName() const;
        TOptional<int64> GetResourceValue() const;
        FString GetResourceValueString() const;
        TOptional<int32> GetWeight() const;
        FString GetWeightString() const;


        static TSharedPtr<FRarityParameterValueModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRarityParameterValueModel, ESPMode::ThreadSafe> FRarityParameterValueModelPtr;
}