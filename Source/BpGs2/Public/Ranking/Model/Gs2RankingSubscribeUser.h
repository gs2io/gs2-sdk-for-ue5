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
#include "Ranking/Domain/Model/Gs2RankingEzSubscribeUserGameSessionDomain.h"
#include "Gs2RankingSubscribeUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingOwnSubscribeUser
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RankingSubscribeUserValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString TargetUserId = "";
};

inline FGs2RankingSubscribeUserValue EzSubscribeUserToFGs2RankingSubscribeUserValue(
    const Gs2::UE5::Ranking::Model::FEzSubscribeUserPtr Model
)
{
    FGs2RankingSubscribeUserValue Value;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.TargetUserId = Model->GetTargetUserId() ? *Model->GetTargetUserId() : "";
    return Value;
}

UCLASS()
class BPGS2_API UGs2RankingSubscribeUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};