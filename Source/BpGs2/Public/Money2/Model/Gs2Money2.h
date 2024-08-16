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
#include "Gs2Money2.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2
{
    GENERATED_BODY()

    Gs2::UE5::Money2::Domain::FEzGs2Money2Ptr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2Money2FunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money2::Service", Category="Game Server Services|GS2-Money2", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Money2 Service(
        FGs2Client Client
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money2::Namespace", Category="Game Server Services|GS2-Money2|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2Money2Namespace Namespace(
        FGs2Money2 Service,
        FString NamespaceName
    );

};