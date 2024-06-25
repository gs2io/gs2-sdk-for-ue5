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

#include "Money2/Model/Gs2Money2EzWalletSummary.h"
#include "Gs2Money2WalletSummary.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2WalletSummary
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Paid = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Free = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Total = 0;
};

inline FGs2Money2WalletSummary EzWalletSummaryToFGs2Money2WalletSummary(
    const Gs2::UE5::Money2::Model::FEzWalletSummaryPtr Model
)
{
    FGs2Money2WalletSummary Value;
    Value.Paid = Model->GetPaid() ? *Model->GetPaid() : 0;
    Value.Free = Model->GetFree() ? *Model->GetFree() : 0;
    Value.Total = Model->GetTotal() ? *Model->GetTotal() : 0;
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzWalletSummaryPtr FGs2Money2WalletSummaryToEzWalletSummary(
    const FGs2Money2WalletSummary Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzWalletSummary>()
        ->WithPaid(Model.Paid)
        ->WithFree(Model.Free)
        ->WithTotal(Model.Total);
}