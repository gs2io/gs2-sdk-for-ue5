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
#include "Showcase/Domain/Model/Gs2ShowcaseEzRandomShowcaseGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ShowcaseRandomShowcase.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseOwnRandomShowcase
{
    GENERATED_BODY()

    Gs2::UE5::Showcase::Domain::Model::FEzRandomShowcaseGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2ShowcaseRandomShowcaseFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::OwnRandomDisplayItem", Category="Game Server Services|GS2-Showcase|Namespace|User|RandomShowcase|RandomDisplayItem", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="RandomDisplayItem") FGs2ShowcaseOwnRandomDisplayItem OwnRandomDisplayItem(
        FGs2ShowcaseOwnRandomShowcase RandomShowcase,
        FString DisplayItemName
    );
};