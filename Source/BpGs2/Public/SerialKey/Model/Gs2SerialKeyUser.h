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
#include "SerialKey/Domain/Model/Gs2SerialKeyEzUserGameSessionDomain.h"
#include "SerialKey/Domain/Model/Gs2SerialKeyEzUserDomain.h"
#include "Gs2SerialKeyUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2SerialKeyOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::SerialKey::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SerialKeyUser
{
    GENERATED_BODY()

    Gs2::UE5::SerialKey::Domain::Model::FEzUserDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2SerialKeyUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SerialKey::SerialKey", Category="Game Server Services|GS2-SerialKey|Namespace|User|SerialKey", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SerialKey") FGs2SerialKeySerialKey SerialKey(
        FGs2SerialKeyUser User,
        FString Code
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SerialKey::OwnSerialKey", Category="Game Server Services|GS2-SerialKey|Namespace|User|SerialKey", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SerialKey") FGs2SerialKeyOwnSerialKey OwnSerialKey(
        FGs2SerialKeyOwnUser User,
        FString Code
    );
};