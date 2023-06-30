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
#include "Lottery/Domain/Model/Gs2LotteryEzBoxItemsGameSessionDomain.h"
#include "Lottery/Model/Gs2LotteryBoxItem.h"
#include "Core/BpGs2Constant.h"
#include "Gs2LotteryBoxItems.generated.h"

USTRUCT(BlueprintType)
struct FGs2LotteryOwnBoxItems
{
    GENERATED_BODY()

    Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2LotteryBoxItemsValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString BoxId = "";
    UPROPERTY(BlueprintReadOnly)
    FString PrizeTableName = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2LotteryBoxItem> Items = TArray<FGs2LotteryBoxItem>();
};

inline FGs2LotteryBoxItemsValue EzBoxItemsToFGs2LotteryBoxItemsValue(
    const Gs2::UE5::Lottery::Model::FEzBoxItemsPtr Model
)
{
    FGs2LotteryBoxItemsValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryBoxItemsFunctionLibrary::EzBoxItemsToFGs2LotteryBoxItemsValue] Model parameter specification is missing."))
        return Value;
    }
    Value.BoxId = Model->GetBoxId() ? *Model->GetBoxId() : "";
    Value.PrizeTableName = Model->GetPrizeTableName() ? *Model->GetPrizeTableName() : "";
    Value.Items = Model->GetItems() ? [&]
    {
        TArray<FGs2LotteryBoxItem> r;
        for (auto v : *Model->GetItems())
        {
            r.Add(EzBoxItemToFGs2LotteryBoxItem(v));
        }
        return r;
    }() : TArray<FGs2LotteryBoxItem>();
    return Value;
}

inline Gs2::UE5::Lottery::Model::FEzBoxItemsPtr FGs2LotteryBoxItemsValueToEzBoxItems(
    const FGs2LotteryBoxItemsValue Model
)
{
    return MakeShared<Gs2::UE5::Lottery::Model::FEzBoxItems>()
        ->WithBoxId(Model.BoxId)
        ->WithPrizeTableName(Model.PrizeTableName)
        ->WithItems([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Lottery::Model::FEzBoxItemPtr>>();
            for (auto v : Model.Items) {
                r->Add(FGs2LotteryBoxItemToEzBoxItem(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2LotteryBoxItemsFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};