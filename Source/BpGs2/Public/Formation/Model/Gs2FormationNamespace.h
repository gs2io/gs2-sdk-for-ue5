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
#include "Formation/Domain/Model/Gs2FormationEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FormationNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Formation::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2FormationNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::MoldModel", Category="Game Server Services|GS2-Formation|Namespace|MoldModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="MoldModel") FGs2FormationMoldModel MoldModel(
        FGs2FormationNamespace Namespace,
        FString MoldModelName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::PropertyFormModel", Category="Game Server Services|GS2-Formation|Namespace|PropertyFormModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="PropertyFormModel") FGs2FormationPropertyFormModel PropertyFormModel(
        FGs2FormationNamespace Namespace,
        FString PropertyFormModelName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::Me", Category="Game Server Services|GS2-Formation|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2FormationOwnUser Me(
        FGs2FormationNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};