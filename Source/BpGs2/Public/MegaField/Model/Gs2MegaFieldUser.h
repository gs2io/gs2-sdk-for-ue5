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
#include "MegaField/Domain/Model/Gs2MegaFieldEzUserGameSessionDomain.h"
#include "Gs2MegaFieldUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2MegaFieldOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::MegaField::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2MegaFieldUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::MegaField::OwnSpatial", Category="Game Server Services|GS2-MegaField|Namespace|User|Spatial", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Spatial") FGs2MegaFieldOwnSpatial OwnSpatial(
        FGs2MegaFieldOwnUser User,
        FString AreaModelName,
        FString LayerModelName
    );
};