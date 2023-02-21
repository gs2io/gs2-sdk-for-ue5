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
#include "Gs2Exchange.generated.h"

USTRUCT(BlueprintType)
struct FGs2Exchange
{
    GENERATED_BODY()

    Gs2::UE5::Exchange::Domain::FEzGs2ExchangePtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2ExchangeFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::Service", Category="Game Server Services|GS2-Exchange", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Exchange Service(
        FGs2Client Client
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::Namespace", Category="Game Server Services|GS2-Exchange|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2ExchangeNamespace Namespace(
        FGs2Exchange Service,
        FString NamespaceName
    );

};