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
#include "Schedule/Domain/Model/Gs2ScheduleEzUserGameSessionDomain.h"
#include "Gs2ScheduleUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2ScheduleOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Schedule::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2ScheduleUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Schedule::OwnTrigger", Category="Game Server Services|GS2-Schedule|Namespace|User|Trigger", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Trigger") FGs2ScheduleOwnTrigger OwnTrigger(
        FGs2ScheduleOwnUser User,
        FString TriggerName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Schedule::OwnEvent", Category="Game Server Services|GS2-Schedule|Namespace|User|Event", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Event") FGs2ScheduleOwnEvent OwnEvent(
        FGs2ScheduleOwnUser User,
        FString EventName
    );
};