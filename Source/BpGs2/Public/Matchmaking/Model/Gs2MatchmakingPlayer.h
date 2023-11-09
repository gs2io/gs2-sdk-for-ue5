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

#include "Matchmaking/Model/Gs2MatchmakingEzPlayer.h"
#include "Matchmaking/Model/Gs2MatchmakingAttribute.h"
#include "Gs2MatchmakingPlayer.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingPlayer
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2MatchmakingAttribute> Attributes = TArray<FGs2MatchmakingAttribute>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString RoleName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FString> DenyUserIds = TArray<FString>();
};

inline FGs2MatchmakingPlayer EzPlayerToFGs2MatchmakingPlayer(
    const Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Model
)
{
    FGs2MatchmakingPlayer Value;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Attributes = Model->GetAttributes() ? [&]
    {
        TArray<FGs2MatchmakingAttribute> r;
        for (auto v : *Model->GetAttributes())
        {r.Add(EzAttributeToFGs2MatchmakingAttribute(v));
        }
        return r;
    }() : TArray<FGs2MatchmakingAttribute>();
    Value.RoleName = Model->GetRoleName() ? *Model->GetRoleName() : "";
    Value.DenyUserIds = Model->GetDenyUserIds() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetDenyUserIds())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzPlayerPtr FGs2MatchmakingPlayerToEzPlayer(
    const FGs2MatchmakingPlayer Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzPlayer>()
        ->WithUserId(Model.UserId)
        ->WithAttributes([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Matchmaking::Model::FEzAttributePtr>>();
            for (auto v : Model.Attributes) {
                r->Add(FGs2MatchmakingAttributeToEzAttribute(v));
            }
            return r;
        }())
        ->WithRoleName(Model.RoleName)
        ->WithDenyUserIds([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.DenyUserIds) {
                r->Add(v);
            }
            return r;
        }());
}