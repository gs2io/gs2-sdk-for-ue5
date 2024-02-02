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
#include "Ranking/Domain/Model/Gs2RankingEzUserGameSessionDomain.h"
#include "Ranking/Domain/Model/Gs2RankingEzUserDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2RankingUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RankingUser
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzUserDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2RankingUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::OwnScore", Category="Game Server Services|GS2-Ranking|Namespace|User|Score", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Score") FGs2RankingOwnScore OwnScore(
        FGs2RankingOwnUser User,
        FString CategoryName,
        FString ScorerUserId,
        FString UniqueId
    );
};