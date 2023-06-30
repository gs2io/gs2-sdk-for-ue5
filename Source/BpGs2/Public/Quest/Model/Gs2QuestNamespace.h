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
#include "Quest/Domain/Model/Gs2QuestEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2QuestNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Quest::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2QuestNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::QuestGroupModel", Category="Game Server Services|GS2-Quest|Namespace|QuestGroupModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="QuestGroupModel") FGs2QuestQuestGroupModel QuestGroupModel(
        FGs2QuestNamespace Namespace,
        FString QuestGroupName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::Me", Category="Game Server Services|GS2-Quest|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2QuestOwnUser Me(
        FGs2QuestNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};