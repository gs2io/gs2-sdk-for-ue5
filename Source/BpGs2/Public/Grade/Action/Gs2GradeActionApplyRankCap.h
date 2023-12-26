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
#include "Grade/Model/Gs2GradeStatus.h"
#include "Grade/Model/Gs2GradeStatus.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2GradeActionApplyRankCap.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2GradeApplyRankCapSuccessDelegate, FGs2GradeOwnStatus, Status, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2GradeApplyRankCapErrorDelegate, FGs2GradeOwnStatus, Status, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2GradeApplyRankCapAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2GradeOwnStatus Status;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2GradeApplyRankCapSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2GradeApplyRankCapErrorDelegate OnError;

    UGs2GradeApplyRankCapAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Grade::Status::Action::ApplyRankCap", Category="Game Server Services|GS2-Grade|Namespace|User|Status|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2GradeApplyRankCapAsyncFunction* ApplyRankCap(
        UObject* WorldContextObject,
        FGs2GradeOwnStatus Status
    );

    virtual void Activate() override;
};