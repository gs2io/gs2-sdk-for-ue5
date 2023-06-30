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
#include "Experience/Domain/Model/Gs2ExperienceEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ExperienceNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExperienceNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Experience::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2ExperienceNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Experience::ExperienceModel", Category="Game Server Services|GS2-Experience|Namespace|ExperienceModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="ExperienceModel") FGs2ExperienceExperienceModel ExperienceModel(
        FGs2ExperienceNamespace Namespace,
        FString ExperienceName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Experience::Me", Category="Game Server Services|GS2-Experience|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2ExperienceOwnUser Me(
        FGs2ExperienceNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};