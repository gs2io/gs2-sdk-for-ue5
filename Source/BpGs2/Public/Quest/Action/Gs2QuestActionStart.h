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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Quest/Model/Gs2QuestConfig.h"
#include "Quest/Model/Gs2QuestUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2QuestActionStart.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestStartSuccessDelegate, FGs2QuestOwnUser, User, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2QuestStartErrorDelegate, FGs2QuestOwnUser, User, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2QuestStartAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2QuestOwnUser User;
    FString QuestGroupName;
    FString QuestName;
    bool Force;
    TArray<FGs2QuestConfig> Config;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestStartSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2QuestStartErrorDelegate OnError;

    UGs2QuestStartAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::Progress::Action::Start", Category="Game Server Services|GS2-Quest|Namespace|User|Progress|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2QuestStartAsyncFunction* Start(
        UObject* WorldContextObject,
        FGs2QuestOwnUser User,
        FString QuestGroupName,
        FString QuestName,
        bool Force,
        TArray<FGs2QuestConfig> Config
    );

    virtual void Activate() override;
};