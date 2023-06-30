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
#include "Ranking/Domain/Model/Gs2RankingEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2RankingNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2RankingNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::CategoryModel", Category="Game Server Services|GS2-Ranking|Namespace|CategoryModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="CategoryModel") FGs2RankingCategoryModel CategoryModel(
        FGs2RankingNamespace Namespace,
        FString CategoryName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::User", Category="Game Server Services|GS2-Ranking|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2RankingUser User(
        FGs2RankingNamespace Namespace,
        FString UserId
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Me", Category="Game Server Services|GS2-Ranking|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2RankingOwnUser Me(
        FGs2RankingNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};