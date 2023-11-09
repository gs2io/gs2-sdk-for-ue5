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
#include "AdReward/Domain/Model/Gs2AdRewardEzPointGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2AdRewardPoint.generated.h"

USTRUCT(BlueprintType)
struct FGs2AdRewardOwnPoint
{
    GENERATED_BODY()

    Gs2::UE5::AdReward::Domain::Model::FEzPointGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2AdRewardPointValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Point = 0;
};

inline FGs2AdRewardPointValue EzPointToFGs2AdRewardPointValue(
    const Gs2::UE5::AdReward::Model::FEzPointPtr Model
)
{
    FGs2AdRewardPointValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AdRewardPointFunctionLibrary::EzPointToFGs2AdRewardPointValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Point = Model->GetPoint() ? *Model->GetPoint() : 0;
    return Value;
}

inline Gs2::UE5::AdReward::Model::FEzPointPtr FGs2AdRewardPointValueToEzPoint(
    const FGs2AdRewardPointValue Model
)
{
    return MakeShared<Gs2::UE5::AdReward::Model::FEzPoint>()
        ->WithPoint(Model.Point);
}

UCLASS()
class BPGS2_API UGs2AdRewardPointFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};