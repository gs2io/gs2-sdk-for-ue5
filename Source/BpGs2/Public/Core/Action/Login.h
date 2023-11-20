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
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Core/Model/Gs2Authenticator.h"
#include "Core/Model/Gs2Client.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Login.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLoginSuccessDelegate, FGs2AccessToken, AccessToken, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLoginErrorDelegate, FGs2AccessToken, AccessToken, const FGs2Error, Error);

UCLASS()
class BPGS2_API ULoginAsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
	FGs2Authenticator Authenticator;
	FGs2Client Client;
	FString UserId;
	FString Password;
	
public:

	UPROPERTY(Category = Gs2, BlueprintAssignable)
	FLoginSuccessDelegate OnSuccess;

	UPROPERTY(Category = Gs2, BlueprintAssignable)
	FLoginErrorDelegate OnError;

	ULoginAsyncFunction(const FObjectInitializer& ObjectInitializer);

	/**
	 * Login Game Server Services Client
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Core::Action::Login", Category="Game Server Services|Core|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
	static ULoginAsyncFunction* Gs2Login(
		UObject* WorldContextObject,
		FGs2Client Client,
		FGs2Authenticator Authenticator,
		FString UserId,
		FString Password
	);
	
	virtual void Activate() override;
};
