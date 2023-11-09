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
#include "Idle/Domain/Model/Gs2IdleEzStatusGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2IdleStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2IdleOwnStatus
{
    GENERATED_BODY()

    Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2IdleStatusValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString CategoryName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 RandomSeed = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 IdleMinutes = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 MaximumIdleMinutes = 0;
};

inline FGs2IdleStatusValue EzStatusToFGs2IdleStatusValue(
    const Gs2::UE5::Idle::Model::FEzStatusPtr Model
)
{
    FGs2IdleStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleStatusFunctionLibrary::EzStatusToFGs2IdleStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.CategoryName = Model->GetCategoryName() ? *Model->GetCategoryName() : "";
    Value.RandomSeed = Model->GetRandomSeed() ? *Model->GetRandomSeed() : 0;
    Value.IdleMinutes = Model->GetIdleMinutes() ? *Model->GetIdleMinutes() : 0;
    Value.MaximumIdleMinutes = Model->GetMaximumIdleMinutes() ? *Model->GetMaximumIdleMinutes() : 0;
    return Value;
}

inline Gs2::UE5::Idle::Model::FEzStatusPtr FGs2IdleStatusValueToEzStatus(
    const FGs2IdleStatusValue Model
)
{
    return MakeShared<Gs2::UE5::Idle::Model::FEzStatus>()
        ->WithCategoryName(Model.CategoryName)
        ->WithRandomSeed(Model.RandomSeed)
        ->WithIdleMinutes(Model.IdleMinutes)
        ->WithMaximumIdleMinutes(Model.MaximumIdleMinutes);
}

UCLASS()
class BPGS2_API UGs2IdleStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};