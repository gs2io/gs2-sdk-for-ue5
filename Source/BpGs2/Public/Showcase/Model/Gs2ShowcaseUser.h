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
#include "Showcase/Domain/Model/Gs2ShowcaseEzUserGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ShowcaseUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Showcase::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2ShowcaseUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::OwnShowcase", Category="Game Server Services|GS2-Showcase|Namespace|User|Showcase", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Showcase") FGs2ShowcaseOwnShowcase OwnShowcase(
        FGs2ShowcaseOwnUser User,
        FString ShowcaseName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::OwnRandomShowcase", Category="Game Server Services|GS2-Showcase|Namespace|User|RandomShowcase", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="RandomShowcase") FGs2ShowcaseOwnRandomShowcase OwnRandomShowcase(
        FGs2ShowcaseOwnUser User,
        FString ShowcaseName
    );
};