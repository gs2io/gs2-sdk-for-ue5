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

#include "Ranking/Model/Gs2RankingEzGlobalRankingSetting.h"
#include "Ranking/Model/Gs2RankingScope.h"
#include "Gs2RankingGlobalRankingSetting.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingGlobalRankingSetting
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 CalculateIntervalMinutes = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2RankingScope> AdditionalScopes = TArray<FGs2RankingScope>();
};

inline FGs2RankingGlobalRankingSetting EzGlobalRankingSettingToFGs2RankingGlobalRankingSetting(
    const Gs2::UE5::Ranking::Model::FEzGlobalRankingSettingPtr Model
)
{
    FGs2RankingGlobalRankingSetting Value;
    Value.CalculateIntervalMinutes = Model->GetCalculateIntervalMinutes() ? *Model->GetCalculateIntervalMinutes() : 0;
    Value.AdditionalScopes = Model->GetAdditionalScopes() ? [&]
    {
        TArray<FGs2RankingScope> r;
        for (auto v : *Model->GetAdditionalScopes())
        {r.Add(EzScopeToFGs2RankingScope(v));
        }
        return r;
    }() : TArray<FGs2RankingScope>();
    return Value;
}

inline Gs2::UE5::Ranking::Model::FEzGlobalRankingSettingPtr FGs2RankingGlobalRankingSettingToEzGlobalRankingSetting(
    const FGs2RankingGlobalRankingSetting Model
)
{
    return MakeShared<Gs2::UE5::Ranking::Model::FEzGlobalRankingSetting>()
        ->WithCalculateIntervalMinutes(Model.CalculateIntervalMinutes)
        ->WithAdditionalScopes([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Ranking::Model::FEzScopePtr>>();
            for (auto v : Model.AdditionalScopes) {
                r->Add(FGs2RankingScopeToEzScope(v));
            }
            return r;
        }());
}