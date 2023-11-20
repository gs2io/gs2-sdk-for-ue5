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
#include "Auth/Model/Gs2AuthAccessToken.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AuthActionLogin.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AuthLoginSuccessDelegate, FGs2AuthAccessToken, AccessToken, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AuthLoginErrorDelegate, FGs2AuthAccessToken, AccessToken, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AuthLoginAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AuthAccessToken AccessToken;
    FString KeyId;
    FString Body;
    FString Signature;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AuthLoginSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AuthLoginErrorDelegate OnError;

    UGs2AuthLoginAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Auth::AccessToken::Action::Login", Category="Game Server Services|GS2-Auth||AccessToken|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AuthLoginAsyncFunction* Login(
        UObject* WorldContextObject,
        FGs2AuthAccessToken AccessToken,
        FString KeyId,
        FString Body,
        FString Signature
    );

    virtual void Activate() override;
};