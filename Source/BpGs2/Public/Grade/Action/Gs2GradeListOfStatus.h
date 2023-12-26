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
#include "Grade/Model/Gs2GradeUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2GradeListOfStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2GradeListOfStatusSuccessDelegate, const TArray<FGs2GradeStatusValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2GradeListOfStatusErrorDelegate, const TArray<FGs2GradeStatusValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2GradeListOfStatusAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2GradeOwnUser User;

public:
    FString GradeName;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2GradeListOfStatusSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2GradeListOfStatusErrorDelegate OnError;

    UGs2GradeListOfStatusAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Grade::Fetch::ListOfStatus", Category="Game Server Services|GS2-Grade|Namespace|User|Status|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2GradeListOfStatusAsyncFunction* ListOfStatus(
        UObject* WorldContextObject,
        FGs2GradeOwnUser User,
        FString GradeName
    );

    virtual void Activate() override;
};