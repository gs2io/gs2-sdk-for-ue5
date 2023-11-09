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
#include "BpGs2/Public/Ranking/Model/Gs2RankingCategoryModel.h"
#include "BpGs2/Public/Ranking/Model/Gs2RankingCategoryModel.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RankingCategoryModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingCategoryModelGetValueSuccessDelegate, FGs2RankingCategoryModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingCategoryModelGetValueErrorDelegate, FGs2RankingCategoryModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RankingCategoryModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RankingCategoryModel CategoryModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingCategoryModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingCategoryModelGetValueErrorDelegate OnError;

    UGs2RankingCategoryModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Fetch::GetValueOfCategoryModel", Category="Game Server Services|GS2-Ranking|Namespace|CategoryModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RankingCategoryModelGetValueAsyncFunction* CategoryModelGetValue(
        UObject* WorldContextObject,
        FGs2RankingCategoryModel CategoryModel
    );

    virtual void Activate() override;
};