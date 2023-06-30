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
#include "Formation/Domain/Model/Gs2FormationEzMoldGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FormationMold.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationOwnMold
{
    GENERATED_BODY()

    Gs2::UE5::Formation::Domain::Model::FEzMoldGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FormationMoldValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    int32 Capacity = 0;
};

inline FGs2FormationMoldValue EzMoldToFGs2FormationMoldValue(
    const Gs2::UE5::Formation::Model::FEzMoldPtr Model
)
{
    FGs2FormationMoldValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationMoldFunctionLibrary::EzMoldToFGs2FormationMoldValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Capacity = Model->GetCapacity() ? *Model->GetCapacity() : 0;
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzMoldPtr FGs2FormationMoldValueToEzMold(
    const FGs2FormationMoldValue Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzMold>()
        ->WithName(Model.Name)
        ->WithUserId(Model.UserId)
        ->WithCapacity(Model.Capacity);
}

UCLASS()
class BPGS2_API UGs2FormationMoldFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::OwnForm", Category="Game Server Services|GS2-Formation|Namespace|User|Mold|Form", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Form") FGs2FormationOwnForm OwnForm(
        FGs2FormationOwnMold Mold,
        int32 Index
    );
};