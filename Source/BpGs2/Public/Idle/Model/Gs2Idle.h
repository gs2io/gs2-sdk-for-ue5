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
#include "Gs2Idle.generated.h"

USTRUCT(BlueprintType)
struct FGs2Idle
{
    GENERATED_BODY()

    Gs2::UE5::Idle::Domain::FEzGs2IdlePtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2IdleFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Idle::Service", Category="Game Server Services|GS2-Idle", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Idle Service(
        FGs2Client Client
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Idle::Namespace", Category="Game Server Services|GS2-Idle|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2IdleNamespace Namespace(
        FGs2Idle Service,
        FString NamespaceName
    );

};