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
#include "Quest/Domain/Model/Gs2QuestEzUserGameSessionDomain.h"
#include "Gs2QuestUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2QuestUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::OwnProgress", Category="Game Server Services|GS2-Quest|Namespace|User|Progress", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Progress") FGs2QuestOwnProgress OwnProgress(
        FGs2QuestOwnUser User
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::OwnCompletedQuestList", Category="Game Server Services|GS2-Quest|Namespace|User|CompletedQuestList", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="CompletedQuestList") FGs2QuestOwnCompletedQuestList OwnCompletedQuestList(
        FGs2QuestOwnUser User,
        FString QuestGroupName
    );
};