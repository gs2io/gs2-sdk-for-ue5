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
#include "SeasonRating/Model/Gs2SeasonRatingNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2SeasonRatingListOfSeasonModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SeasonRatingListOfSeasonModelSuccessDelegate, const TArray<FGs2SeasonRatingSeasonModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SeasonRatingListOfSeasonModelErrorDelegate, const TArray<FGs2SeasonRatingSeasonModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2SeasonRatingListOfSeasonModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2SeasonRatingNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2SeasonRatingListOfSeasonModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2SeasonRatingListOfSeasonModelErrorDelegate OnError;

    UGs2SeasonRatingListOfSeasonModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::SeasonRating::Fetch::ListOfSeasonModel", Category="Game Server Services|GS2-SeasonRating|Namespace|SeasonModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2SeasonRatingListOfSeasonModelAsyncFunction* ListOfSeasonModel(
        UObject* WorldContextObject,
        FGs2SeasonRatingNamespace Namespace
    );

    virtual void Activate() override;
};