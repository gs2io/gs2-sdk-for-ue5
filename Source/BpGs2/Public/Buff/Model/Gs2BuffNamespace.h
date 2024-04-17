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
#include "Buff/Domain/Model/Gs2BuffEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2BuffNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2BuffNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Buff::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2BuffNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Buff::BuffEntryModel", Category="Game Server Services|GS2-Buff|Namespace|BuffEntryModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="BuffEntryModel") FGs2BuffBuffEntryModel BuffEntryModel(
        FGs2BuffNamespace Namespace,
        FString BuffEntryName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Buff::Me", Category="Game Server Services|GS2-Buff|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2BuffOwnUser Me(
        FGs2BuffNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};