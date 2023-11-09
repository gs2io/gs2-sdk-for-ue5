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
#include "Lottery/Domain/Model/Gs2LotteryEzLotteryModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2LotteryLotteryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2LotteryLotteryModel
{
    GENERATED_BODY()

    Gs2::UE5::Lottery::Domain::Model::FEzLotteryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2LotteryLotteryModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Mode = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PrizeTableName = "";
};

inline FGs2LotteryLotteryModelValue EzLotteryModelToFGs2LotteryLotteryModelValue(
    const Gs2::UE5::Lottery::Model::FEzLotteryModelPtr Model
)
{
    FGs2LotteryLotteryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryLotteryModelFunctionLibrary::EzLotteryModelToFGs2LotteryLotteryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Mode = Model->GetMode() ? *Model->GetMode() : "";
    Value.PrizeTableName = Model->GetPrizeTableName() ? *Model->GetPrizeTableName() : "";
    return Value;
}

inline Gs2::UE5::Lottery::Model::FEzLotteryModelPtr FGs2LotteryLotteryModelValueToEzLotteryModel(
    const FGs2LotteryLotteryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Lottery::Model::FEzLotteryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithMode(Model.Mode)
        ->WithPrizeTableName(Model.PrizeTableName);
}

UCLASS()
class BPGS2_API UGs2LotteryLotteryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};