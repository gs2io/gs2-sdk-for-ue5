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
#include "BpGs2/Public/Quest/Model/Gs2QuestNamespace.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2QuestListOfQuestGroupModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestListOfQuestGroupModelSuccessDelegate, const TArray<FGs2QuestQuestGroupModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestListOfQuestGroupModelErrorDelegate, const TArray<FGs2QuestQuestGroupModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2QuestListOfQuestGroupModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2QuestNamespace Namespace;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2QuestListOfQuestGroupModelSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2QuestListOfQuestGroupModelErrorDelegate OnError;

    UGs2QuestListOfQuestGroupModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::Fetch::ListOfQuestGroupModel", Category="Game Server Services|GS2-Quest|Namespace|QuestGroupModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2QuestListOfQuestGroupModelAsyncFunction* ListOfQuestGroupModel(
        UObject* WorldContextObject,
        FGs2QuestNamespace Namespace
    );

    virtual void Activate() override;
};