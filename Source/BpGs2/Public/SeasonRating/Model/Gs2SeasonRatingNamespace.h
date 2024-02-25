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
#include "SeasonRating/Domain/Model/Gs2SeasonRatingEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SeasonRatingNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2SeasonRatingNamespace
{
    GENERATED_BODY()

    Gs2::UE5::SeasonRating::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2SeasonRatingNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SeasonRating::SeasonModel", Category="Game Server Services|GS2-SeasonRating|Namespace|SeasonModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SeasonModel") FGs2SeasonRatingSeasonModel SeasonModel(
        FGs2SeasonRatingNamespace Namespace,
        FString SeasonName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SeasonRating::Me", Category="Game Server Services|GS2-SeasonRating|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2SeasonRatingOwnUser Me(
        FGs2SeasonRatingNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};