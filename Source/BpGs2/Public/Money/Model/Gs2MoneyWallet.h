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
#include "Money/Domain/Model/Gs2MoneyEzWalletGameSessionDomain.h"
#include "Gs2MoneyWallet.generated.h"

USTRUCT(BlueprintType)
struct FGs2MoneyOwnWallet
{
    GENERATED_BODY()

    Gs2::UE5::Money::Domain::Model::FEzWalletGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MoneyWalletValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 Slot = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 Paid = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 Free = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 UpdatedAt = 0;
};

inline FGs2MoneyWalletValue EzWalletToFGs2MoneyWalletValue(
    const Gs2::UE5::Money::Model::FEzWalletPtr Model
)
{
    FGs2MoneyWalletValue Value;
    Value.Slot = Model->GetSlot() ? *Model->GetSlot() : 0;
    Value.Paid = Model->GetPaid() ? *Model->GetPaid() : 0;
    Value.Free = Model->GetFree() ? *Model->GetFree() : 0;
    Value.UpdatedAt = Model->GetUpdatedAt() ? *Model->GetUpdatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Money::Model::FEzWalletPtr FGs2MoneyWalletValueToEzWallet(
    const FGs2MoneyWalletValue Model
)
{
    return MakeShared<Gs2::UE5::Money::Model::FEzWallet>()
        ->WithSlot(Model.Slot)
        ->WithPaid(Model.Paid)
        ->WithFree(Model.Free)
        ->WithUpdatedAt(Model.UpdatedAt);
}

UCLASS()
class BPGS2_API UGs2MoneyWalletFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};