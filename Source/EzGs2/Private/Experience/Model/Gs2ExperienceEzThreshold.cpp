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

#include "EzGs2/Public/Experience/Model/Gs2ExperienceEzThreshold.h"

namespace Gs2::UE5::Experience::Model
{

    TSharedPtr<FEzThreshold> FEzThreshold::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzThreshold> FEzThreshold::WithValues(
        const TSharedPtr<TArray<int64>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }
    TOptional<FString> FEzThreshold::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<int64>> FEzThreshold::GetValues() const
    {
        return ValuesValue;
    }

    Gs2::Experience::Model::FThresholdPtr FEzThreshold::ToModel() const
    {
        return MakeShared<Gs2::Experience::Model::FThreshold>()
            ->WithMetadata(MetadataValue)
            ->WithValues(ValuesValue);
    }

    TSharedPtr<FEzThreshold> FEzThreshold::FromModel(const Gs2::Experience::Model::FThresholdPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzThreshold>()
            ->WithMetadata(Model->GetMetadata())
            ->WithValues(Model->GetValues());
    }
}