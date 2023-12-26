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

#include "Grade/Model/Gs2GradeEzGradeModel.h"

namespace Gs2::UE5::Grade::Model
{

    TSharedPtr<FEzGradeModel> FEzGradeModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzGradeModel> FEzGradeModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGradeModel> FEzGradeModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzGradeModel> FEzGradeModel::WithGradeEntries(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzGradeEntryModel>>> GradeEntries
    )
    {
        this->GradeEntriesValue = GradeEntries;
        return SharedThis(this);
    }

    TSharedPtr<FEzGradeModel> FEzGradeModel::WithAcquireActionRates(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzAcquireActionRate>>> AcquireActionRates
    )
    {
        this->AcquireActionRatesValue = AcquireActionRates;
        return SharedThis(this);
    }
    TOptional<FString> FEzGradeModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzGradeModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzGradeModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzGradeEntryModel>>> FEzGradeModel::GetGradeEntries() const
    {
        return GradeEntriesValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzAcquireActionRate>>> FEzGradeModel::GetAcquireActionRates() const
    {
        return AcquireActionRatesValue;
    }

    Gs2::Grade::Model::FGradeModelPtr FEzGradeModel::ToModel() const
    {
        return MakeShared<Gs2::Grade::Model::FGradeModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithExperienceModelId(ExperienceModelIdValue)
            ->WithGradeEntries([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Grade::Model::FGradeEntryModel>>>();
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
            )
            ->WithAcquireActionRates([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Grade::Model::FAcquireActionRate>>>();
                    if (AcquireActionRatesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AcquireActionRatesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzGradeModel> FEzGradeModel::FromModel(const Gs2::Grade::Model::FGradeModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGradeModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithExperienceModelId(Model->GetExperienceModelId())
            ->WithGradeEntries([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzGradeEntryModel>>>();
                    if (Model->GetGradeEntries() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetGradeEntries())
                    {
                        v->Add(FEzGradeEntryModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithAcquireActionRates([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireActionRate>>>();
                    if (Model->GetAcquireActionRates() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAcquireActionRates())
                    {
                        v->Add(FEzAcquireActionRate::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}