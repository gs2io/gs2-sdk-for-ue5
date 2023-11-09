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
#include "BpGs2/Public/Quest/Model/Gs2QuestProgress.h"
#include "BpGs2/Public/Quest/Model/Gs2QuestProgress.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2QuestProgressGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestProgressGetValueSuccessDelegate, FGs2QuestProgressValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestProgressGetValueErrorDelegate, FGs2QuestProgressValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2QuestProgressGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2QuestOwnProgress Progress;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestProgressGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestProgressGetValueErrorDelegate OnError;

    UGs2QuestProgressGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::Fetch::GetValueOfProgress", Category="Game Server Services|GS2-Quest|Namespace|User|Progress|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2QuestProgressGetValueAsyncFunction* ProgressGetValue(
        UObject* WorldContextObject,
        FGs2QuestOwnProgress Progress
    );

    virtual void Activate() override;
};