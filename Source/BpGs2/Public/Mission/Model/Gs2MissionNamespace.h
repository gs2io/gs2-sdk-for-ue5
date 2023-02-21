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
#include "Mission/Domain/Model/Gs2MissionEzNamespaceDomain.h"
#include "Gs2MissionNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2MissionNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::MissionGroupModel", Category="Game Server Services|GS2-Mission|Namespace|MissionGroupModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="MissionGroupModel") FGs2MissionMissionGroupModel MissionGroupModel(
        FGs2MissionNamespace Namespace,
        FString MissionGroupName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::CounterModel", Category="Game Server Services|GS2-Mission|Namespace|CounterModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="CounterModel") FGs2MissionCounterModel CounterModel(
        FGs2MissionNamespace Namespace,
        FString CounterName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::Me", Category="Game Server Services|GS2-Mission|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2MissionOwnUser Me(
        FGs2MissionNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};