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
#include "Core/Model/Gs2Client.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2Region.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Initialize.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInitializeSuccessDelegate, FGs2Client, Client, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInitializeErrorDelegate, FGs2Client, Client, const FGs2Error, Error);

UCLASS()
class BPGS2_API UInitializeAsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
	FString ClientId;
	FString ClientSecret;
	EGs2Region Region;
	
public:
	UPROPERTY(Category = Gs2, BlueprintAssignable)
	FInitializeSuccessDelegate OnSuccess;

	UPROPERTY(Category = Gs2, BlueprintAssignable)
	FInitializeErrorDelegate OnError;

	UInitializeAsyncFunction(const FObjectInitializer& ObjectInitializer);

	/**
	 * Initialize Game Server Services Client
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Core::Action::Initialize", Category="Game Server Services|Core|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
	static UInitializeAsyncFunction* Gs2Initialize(
		UObject* WorldContextObject,
		FString ClientId,
		FString ClientSecret,
		EGs2Region Region
	);
	
	virtual void Activate() override;
};
