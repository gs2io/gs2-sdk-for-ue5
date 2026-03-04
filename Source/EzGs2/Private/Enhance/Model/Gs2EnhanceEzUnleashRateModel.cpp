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

#include "Enhance/Model/Gs2EnhanceEzUnleashRateModel.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashRateModel> FEzUnleashRateModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateModel> FEzUnleashRateModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateModel> FEzUnleashRateModel::WithTargetInventoryModelId(
        const TOptional<FString> TargetInventoryModelId
    )
    {
        this->TargetInventoryModelIdValue = TargetInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateModel> FEzUnleashRateModel::WithGradeModelId(
        const TOptional<FString> GradeModelId
    )
    {
        this->GradeModelIdValue = GradeModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateModel> FEzUnleashRateModel::WithGradeEntries(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModel>>> GradeEntries
    )
    {
        this->GradeEntriesValue = GradeEntries;
        return SharedThis(this);
    }
    TOptional<FString> FEzUnleashRateModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzUnleashRateModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzUnleashRateModel::GetTargetInventoryModelId() const
    {
        return TargetInventoryModelIdValue;
    }
    TOptional<FString> FEzUnleashRateModel::GetGradeModelId() const
    {
        return GradeModelIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModel>>> FEzUnleashRateModel::GetGradeEntries() const
    {
        return GradeEntriesValue;
    }

    Gs2::Enhance::Model::FUnleashRateModelPtr FEzUnleashRateModel::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashRateModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTargetInventoryModelId(TargetInventoryModelIdValue)
            ->WithGradeModelId(GradeModelIdValue)
            ->WithGradeEntries([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FUnleashRateEntryModel>>>();
                    if (GradeEntriesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *GradeEntriesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzUnleashRateModel> FEzUnleashRateModel::FromModel(const Gs2::Enhance::Model::FUnleashRateModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashRateModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTargetInventoryModelId(Model->GetTargetInventoryModelId())
            ->WithGradeModelId(Model->GetGradeModelId())
            ->WithGradeEntries([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzUnleashRateEntryModel>>>();
                    if (Model->GetGradeEntries() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetGradeEntries())
                    {
                        v->Add(FEzUnleashRateEntryModel::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}