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
#include "Enhance/Domain/Model/Gs2EnhanceEzUserGameSessionDomain.h"
#include "Gs2EnhanceUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Enhance::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2EnhanceUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enhance::OwnProgress", Category="Game Server Services|GS2-Enhance|Namespace|User|Progress", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Progress") FGs2EnhanceOwnProgress OwnProgress(
        FGs2EnhanceOwnUser User
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enhance::OwnEnhance", Category="Game Server Services|GS2-Enhance|Namespace|User|Enhance", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Enhance") FGs2EnhanceOwnEnhance OwnEnhance(
        FGs2EnhanceOwnUser User
    );
};