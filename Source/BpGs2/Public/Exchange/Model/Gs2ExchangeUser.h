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
#include "Exchange/Domain/Model/Gs2ExchangeEzUserGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ExchangeUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Exchange::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2ExchangeUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::OwnExchange", Category="Game Server Services|GS2-Exchange|Namespace|User|Exchange", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Exchange") FGs2ExchangeOwnExchange OwnExchange(
        FGs2ExchangeOwnUser User
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::OwnAwait", Category="Game Server Services|GS2-Exchange|Namespace|User|Await", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Await") FGs2ExchangeOwnAwait OwnAwait(
        FGs2ExchangeOwnUser User,
        FString AwaitName
    );
};