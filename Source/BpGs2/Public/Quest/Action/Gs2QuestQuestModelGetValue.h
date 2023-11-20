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
#include "Quest/Model/Gs2QuestQuestModel.h"
#include "Quest/Model/Gs2QuestQuestModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2QuestQuestModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestQuestModelGetValueSuccessDelegate, FGs2QuestQuestModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestQuestModelGetValueErrorDelegate, FGs2QuestQuestModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2QuestQuestModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2QuestQuestModel QuestModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestQuestModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestQuestModelGetValueErrorDelegate OnError;

    UGs2QuestQuestModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::Fetch::GetValueOfQuestModel", Category="Game Server Services|GS2-Quest|Namespace|QuestGroupModel|QuestModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2QuestQuestModelGetValueAsyncFunction* QuestModelGetValue(
        UObject* WorldContextObject,
        FGs2QuestQuestModel QuestModel
    );

    virtual void Activate() override;
};