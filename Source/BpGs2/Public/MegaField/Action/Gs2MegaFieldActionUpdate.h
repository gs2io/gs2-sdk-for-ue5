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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "BpGs2/Public/MegaField/Model/Gs2MegaFieldSpatial.h"
#include "BpGs2/Public/MegaField/Model/Gs2MegaFieldMyPosition.h"
#include "BpGs2/Public/MegaField/Model/Gs2MegaFieldScope.h"
#include "BpGs2/Public/MegaField/Model/Gs2MegaFieldSpatial.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MegaFieldActionUpdate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MegaFieldUpdateSuccessDelegate, const TArray<FGs2MegaFieldSpatial>, Spatials, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MegaFieldUpdateErrorDelegate, const TArray<FGs2MegaFieldSpatial>, Spatials, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MegaFieldUpdateAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MegaFieldOwnSpatial Spatial;
    FGs2MegaFieldMyPosition Position;
    TArray<FGs2MegaFieldScope> Scopes;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MegaFieldUpdateSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MegaFieldUpdateErrorDelegate OnError;

    UGs2MegaFieldUpdateAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::MegaField::Spatial::Action::Update", Category="Game Server Services|GS2-MegaField|Namespace|User|Spatial|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MegaFieldUpdateAsyncFunction* Update(
        UObject* WorldContextObject,
        FGs2MegaFieldOwnSpatial Spatial,
        FGs2MegaFieldMyPosition Position,
        TArray<FGs2MegaFieldScope> Scopes
    );

    virtual void Activate() override;
};