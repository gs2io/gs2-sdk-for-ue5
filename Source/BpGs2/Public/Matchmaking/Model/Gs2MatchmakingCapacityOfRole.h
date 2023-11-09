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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"

#include "Matchmaking/Model/Gs2MatchmakingEzCapacityOfRole.h"
#include "Matchmaking/Model/Gs2MatchmakingPlayer.h"
#include "Gs2MatchmakingCapacityOfRole.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingCapacityOfRole
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString RoleName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FString> RoleAliases = TArray<FString>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Capacity = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2MatchmakingPlayer> Participants = TArray<FGs2MatchmakingPlayer>();
};

inline FGs2MatchmakingCapacityOfRole EzCapacityOfRoleToFGs2MatchmakingCapacityOfRole(
    const Gs2::UE5::Matchmaking::Model::FEzCapacityOfRolePtr Model
)
{
    FGs2MatchmakingCapacityOfRole Value;
    Value.RoleName = Model->GetRoleName() ? *Model->GetRoleName() : "";
    Value.RoleAliases = Model->GetRoleAliases() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetRoleAliases())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    Value.Capacity = Model->GetCapacity() ? *Model->GetCapacity() : 0;
    Value.Participants = Model->GetParticipants() ? [&]
    {
        TArray<FGs2MatchmakingPlayer> r;
        for (auto v : *Model->GetParticipants())
        {r.Add(EzPlayerToFGs2MatchmakingPlayer(v));
        }
        return r;
    }() : TArray<FGs2MatchmakingPlayer>();
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzCapacityOfRolePtr FGs2MatchmakingCapacityOfRoleToEzCapacityOfRole(
    const FGs2MatchmakingCapacityOfRole Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>()
        ->WithRoleName(Model.RoleName)
        ->WithRoleAliases([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.RoleAliases) {
                r->Add(v);
            }
            return r;
        }())
        ->WithCapacity(Model.Capacity)
        ->WithParticipants([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Matchmaking::Model::FEzPlayerPtr>>();
            for (auto v : Model.Participants) {
                r->Add(FGs2MatchmakingPlayerToEzPlayer(v));
            }
            return r;
        }());
}