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
#include "SkillTree/Domain/Model/Gs2SkillTreeEzUserGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SkillTreeUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2SkillTreeOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::SkillTree::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2SkillTreeUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SkillTree::OwnStatus", Category="Game Server Services|GS2-SkillTree|Namespace|User|Status", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Status") FGs2SkillTreeOwnStatus OwnStatus(
        FGs2SkillTreeOwnUser User
    );
};