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
#include "Gs2Guard.generated.h"

USTRUCT(BlueprintType)
struct FGs2Guard
{
    GENERATED_BODY()

    Gs2::UE5::Guard::Domain::FEzGs2GuardPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2GuardFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Guard::Service", Category="Game Server Services|GS2-Guard", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Guard Service(
        FGs2Client Client
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Guard::Namespace", Category="Game Server Services|GS2-Guard|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2GuardNamespace Namespace(
        FGs2Guard Service,
        FString NamespaceName
    );

};