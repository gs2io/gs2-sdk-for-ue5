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

#include "Ranking/Model/Gs2RankingEzGlobalRankingSetting.h"

namespace Gs2::UE5::Ranking::Model
{

    TSharedPtr<FEzGlobalRankingSetting> FEzGlobalRankingSetting::WithCalculateIntervalMinutes(
        const TOptional<int32> CalculateIntervalMinutes
    )
    {
        this->CalculateIntervalMinutesValue = CalculateIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingSetting> FEzGlobalRankingSetting::WithAdditionalScopes(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking::Model::FEzScope>>> AdditionalScopes
    )
    {
        this->AdditionalScopesValue = AdditionalScopes;
        return SharedThis(this);
    }
    TOptional<int32> FEzGlobalRankingSetting::GetCalculateIntervalMinutes() const
    {
        return CalculateIntervalMinutesValue;
    }

    FString FEzGlobalRankingSetting::GetCalculateIntervalMinutesString() const
    {
        if (!CalculateIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateIntervalMinutesValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking::Model::FEzScope>>> FEzGlobalRankingSetting::GetAdditionalScopes() const
    {
        return AdditionalScopesValue;
    }

    Gs2::Ranking::Model::FGlobalRankingSettingPtr FEzGlobalRankingSetting::ToModel() const
    {
        return MakeShared<Gs2::Ranking::Model::FGlobalRankingSetting>()
            ->WithCalculateIntervalMinutes(CalculateIntervalMinutesValue)
            ->WithAdditionalScopes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Ranking::Model::FScope>>>();
                    if (AdditionalScopesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AdditionalScopesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzGlobalRankingSetting> FEzGlobalRankingSetting::FromModel(const Gs2::Ranking::Model::FGlobalRankingSettingPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGlobalRankingSetting>()
            ->WithCalculateIntervalMinutes(Model->GetCalculateIntervalMinutes())
            ->WithAdditionalScopes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzScope>>>();
                    if (Model->GetAdditionalScopes() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAdditionalScopes())
                    {
                        v->Add(FEzScope::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}