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

#include "Mission/Model/Gs2MissionEzCounterModel.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzCounterModel> FEzCounterModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounterModel> FEzCounterModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounterModel> FEzCounterModel::WithScopes(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterScopeModel>>> Scopes
    )
    {
        this->ScopesValue = Scopes;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounterModel> FEzCounterModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzCounterModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzCounterModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterScopeModel>>> FEzCounterModel::GetScopes() const
    {
        return ScopesValue;
    }
    TOptional<FString> FEzCounterModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    Gs2::Mission::Model::FCounterModelPtr FEzCounterModel::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FCounterModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithScopes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Mission::Model::FCounterScopeModel>>>();
                    if (ScopesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ScopesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(ChallengePeriodEventIdValue);
    }

    TSharedPtr<FEzCounterModel> FEzCounterModel::FromModel(const Gs2::Mission::Model::FCounterModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCounterModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithScopes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzCounterScopeModel>>>();
                    if (Model->GetScopes() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetScopes())
                    {
                        v->Add(FEzCounterScopeModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(Model->GetChallengePeriodEventId());
    }
}