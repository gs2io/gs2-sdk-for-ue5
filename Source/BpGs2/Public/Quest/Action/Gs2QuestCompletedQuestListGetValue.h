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
#include "Quest/Model/Gs2QuestCompletedQuestList.h"
#include "Quest/Model/Gs2QuestCompletedQuestList.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2QuestCompletedQuestListGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestCompletedQuestListGetValueSuccessDelegate, FGs2QuestCompletedQuestListValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestCompletedQuestListGetValueErrorDelegate, FGs2QuestCompletedQuestListValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2QuestCompletedQuestListGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2QuestOwnCompletedQuestList CompletedQuestList;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestCompletedQuestListGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestCompletedQuestListGetValueErrorDelegate OnError;

    UGs2QuestCompletedQuestListGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::Fetch::GetValueOfCompletedQuestList", Category="Game Server Services|GS2-Quest|Namespace|User|CompletedQuestList|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2QuestCompletedQuestListGetValueAsyncFunction* CompletedQuestListGetValue(
        UObject* WorldContextObject,
        FGs2QuestOwnCompletedQuestList CompletedQuestList
    );

    virtual void Activate() override;
};