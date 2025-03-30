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

#include "Money2/Model/Gs2Money2EzDepositTransaction.h"
#include "Gs2Money2DepositTransaction.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2DepositTransaction
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    double Price = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Currency = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Count = 0;
};

inline FGs2Money2DepositTransaction EzDepositTransactionToFGs2Money2DepositTransaction(
    const Gs2::UE5::Money2::Model::FEzDepositTransactionPtr Model
)
{
    FGs2Money2DepositTransaction Value;
    Value.Price = Model->GetPrice() ? *Model->GetPrice() : 0;
    Value.Currency = Model->GetCurrency() ? *Model->GetCurrency() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzDepositTransactionPtr FGs2Money2DepositTransactionToEzDepositTransaction(
    const FGs2Money2DepositTransaction Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzDepositTransaction>()
        ->WithPrice(Model.Price)
        ->WithCurrency(Model.Currency)
        ->WithCount(Model.Count);
}