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
#include "Money2/Domain/Model/Gs2Money2EzUserGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2Money2User.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2OwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Money2::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2Money2UserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money2::OwnWallet", Category="Game Server Services|GS2-Money2|Namespace|User|Wallet", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Wallet") FGs2Money2OwnWallet OwnWallet(
        FGs2Money2OwnUser User,
        int32 Slot
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money2::OwnSubscriptionStatus", Category="Game Server Services|GS2-Money2|Namespace|User|SubscriptionStatus", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SubscriptionStatus") FGs2Money2OwnSubscriptionStatus OwnSubscriptionStatus(
        FGs2Money2OwnUser User,
        FString ContentName
    );
};