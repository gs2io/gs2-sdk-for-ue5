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
#include "Account/Model/Gs2AccountPlatformId.h"
#include "Account/Model/Gs2AccountPlatformId.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AccountActionAddPlatformIdSetting.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountAddPlatformIdSettingSuccessDelegate, FGs2AccountOwnPlatformId, PlatformId, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountAddPlatformIdSettingErrorDelegate, FGs2AccountOwnPlatformId, PlatformId, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AccountAddPlatformIdSettingAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AccountOwnPlatformId PlatformId;
    int32 Type;
    FString UserIdentifier;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountAddPlatformIdSettingSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountAddPlatformIdSettingErrorDelegate OnError;

    UGs2AccountAddPlatformIdSettingAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::PlatformId::Action::AddPlatformIdSetting", Category="Game Server Services|GS2-Account|Namespace|Account|PlatformId|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AccountAddPlatformIdSettingAsyncFunction* AddPlatformIdSetting(
        UObject* WorldContextObject,
        FGs2AccountOwnPlatformId PlatformId
    );

    virtual void Activate() override;
};