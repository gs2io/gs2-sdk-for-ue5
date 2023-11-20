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
#include "Quest/Model/Gs2QuestQuestGroupModel.h"
#include "Quest/Model/Gs2QuestQuestGroupModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2QuestQuestGroupModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestQuestGroupModelGetValueSuccessDelegate, FGs2QuestQuestGroupModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestQuestGroupModelGetValueErrorDelegate, FGs2QuestQuestGroupModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2QuestQuestGroupModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2QuestQuestGroupModel QuestGroupModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestQuestGroupModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestQuestGroupModelGetValueErrorDelegate OnError;

    UGs2QuestQuestGroupModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::Fetch::GetValueOfQuestGroupModel", Category="Game Server Services|GS2-Quest|Namespace|QuestGroupModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2QuestQuestGroupModelGetValueAsyncFunction* QuestGroupModelGetValue(
        UObject* WorldContextObject,
        FGs2QuestQuestGroupModel QuestGroupModel
    );

    virtual void Activate() override;
};