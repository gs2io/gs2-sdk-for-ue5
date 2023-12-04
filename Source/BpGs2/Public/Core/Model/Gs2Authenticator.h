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
#include "Account/Model/Gs2AccountNamespace.h"
#include "Key/Model/Gs2KeyKey.h"
#include "Util/Authentication/Gs2AccountAuthenticator.h"
#include "Gs2Authenticator.generated.h"

USTRUCT(BlueprintType)
struct FGs2Authenticator
{
    GENERATED_BODY()
    
    Gs2::UE5::Util::FGs2AccountAuthenticatorPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2AuthenticatorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Core::CreateGs2Authenticator", Category="Game Server Services|Core")
	static UPARAM(DisplayName="Authenticator") FGs2Authenticator CreateGs2Authenticator(
		const FGs2AccountNamespace Namespace,
		const FGs2KeyKey Key
	);
};