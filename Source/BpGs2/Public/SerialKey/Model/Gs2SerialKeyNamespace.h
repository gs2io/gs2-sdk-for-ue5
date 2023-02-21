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
#include "SerialKey/Domain/Model/Gs2SerialKeyEzNamespaceDomain.h"
#include "Gs2SerialKeyNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2SerialKeyNamespace
{
    GENERATED_BODY()

    Gs2::UE5::SerialKey::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2SerialKeyNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SerialKey::CampaignModel", Category="Game Server Services|GS2-SerialKey|Namespace|CampaignModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="CampaignModel") FGs2SerialKeyCampaignModel CampaignModel(
        FGs2SerialKeyNamespace Namespace,
        FString CampaignModelName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SerialKey::User", Category="Game Server Services|GS2-SerialKey|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2SerialKeyUser User(
        FGs2SerialKeyNamespace Namespace,
        FString UserId
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SerialKey::Me", Category="Game Server Services|GS2-SerialKey|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2SerialKeyOwnUser Me(
        FGs2SerialKeyNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};