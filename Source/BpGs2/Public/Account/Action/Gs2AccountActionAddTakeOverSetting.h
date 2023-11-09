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
#include "BpGs2/Public/Account/Model/Gs2AccountTakeOver.h"
#include "BpGs2/Public/Account/Model/Gs2AccountTakeOver.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AccountActionAddTakeOverSetting.generated.h"
  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountAddTakeOverSettingSuccessDelegate, FGs2AccountOwnTakeOver, TakeOver, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountAddTakeOverSettingErrorDelegate, FGs2AccountOwnTakeOver, TakeOver, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AccountAddTakeOverSettingAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AccountOwnTakeOver TakeOver;
    FString UserIdentifier;
    FString Password;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountAddTakeOverSettingSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountAddTakeOverSettingErrorDelegate OnError;

    UGs2AccountAddTakeOverSettingAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::TakeOver::Action::AddTakeOverSetting", Category="Game Server Services|GS2-Account|Namespace|Account|TakeOver|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AccountAddTakeOverSettingAsyncFunction* AddTakeOverSetting(
        UObject* WorldContextObject,
        FGs2AccountOwnTakeOver TakeOver,
        int32 Type,
        FString UserIdentifier,
        FString Password
    );

    virtual void Activate() override;
};