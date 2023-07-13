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
#include "Gs2LoginReward.generated.h"

USTRUCT(BlueprintType)
struct FGs2LoginReward
{
    GENERATED_BODY()

    Gs2::UE5::LoginReward::Domain::FEzGs2LoginRewardPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2LoginRewardFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::LoginReward::Service", Category="Game Server Services|GS2-LoginReward", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2LoginReward Service(
        FGs2Client Client
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::LoginReward::Namespace", Category="Game Server Services|GS2-LoginReward|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2LoginRewardNamespace Namespace(
        FGs2LoginReward Service,
        FString NamespaceName
    );

};