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
#include "Mission/Domain/Model/Gs2MissionEzUserGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MissionUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2MissionUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::OwnCounter", Category="Game Server Services|GS2-Mission|Namespace|User|Counter", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Counter") FGs2MissionOwnCounter OwnCounter(
        FGs2MissionOwnUser User,
        FString CounterName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::OwnComplete", Category="Game Server Services|GS2-Mission|Namespace|User|Complete", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Complete") FGs2MissionOwnComplete OwnComplete(
        FGs2MissionOwnUser User,
        FString MissionGroupName
    );
};