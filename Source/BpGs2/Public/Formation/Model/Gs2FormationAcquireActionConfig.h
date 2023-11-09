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

#include "Formation/Model/Gs2FormationEzAcquireActionConfig.h"
#include "Formation/Model/Gs2FormationConfig.h"
#include "Gs2FormationAcquireActionConfig.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationAcquireActionConfig
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2FormationConfig> Config = TArray<FGs2FormationConfig>();
};

inline FGs2FormationAcquireActionConfig EzAcquireActionConfigToFGs2FormationAcquireActionConfig(
    const Gs2::UE5::Formation::Model::FEzAcquireActionConfigPtr Model
)
{
    FGs2FormationAcquireActionConfig Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Config = Model->GetConfig() ? [&]
    {
        TArray<FGs2FormationConfig> r;
        for (auto v : *Model->GetConfig())
        {r.Add(EzConfigToFGs2FormationConfig(v));
        }
        return r;
    }() : TArray<FGs2FormationConfig>();
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzAcquireActionConfigPtr FGs2FormationAcquireActionConfigToEzAcquireActionConfig(
    const FGs2FormationAcquireActionConfig Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzAcquireActionConfig>()
        ->WithName(Model.Name)
        ->WithConfig([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Formation::Model::FEzConfigPtr>>();
            for (auto v : Model.Config) {
                r->Add(FGs2FormationConfigToEzConfig(v));
            }
            return r;
        }());
}