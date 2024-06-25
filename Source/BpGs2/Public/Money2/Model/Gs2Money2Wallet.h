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
#include "Money2/Domain/Model/Gs2Money2EzWalletGameSessionDomain.h"
#include "Money2/Model/Gs2Money2WalletSummary.h"
#include "Core/BpGs2Constant.h"
#include "Gs2Money2Wallet.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2OwnWallet
{
    GENERATED_BODY()

    Gs2::UE5::Money2::Domain::Model::FEzWalletGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2Money2WalletValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 Slot = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2Money2WalletSummary Summary = FGs2Money2WalletSummary();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    bool SharedFreeCurrency = false;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 UpdatedAt = 0;
};

inline FGs2Money2WalletValue EzWalletToFGs2Money2WalletValue(
    const Gs2::UE5::Money2::Model::FEzWalletPtr Model
)
{
    FGs2Money2WalletValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2WalletFunctionLibrary::EzWalletToFGs2Money2WalletValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Slot = Model->GetSlot() ? *Model->GetSlot() : 0;
    Value.Summary = Model->GetSummary() ? EzWalletSummaryToFGs2Money2WalletSummary(Model->GetSummary()) : FGs2Money2WalletSummary();
    Value.SharedFreeCurrency = Model->GetSharedFreeCurrency() ? *Model->GetSharedFreeCurrency() : false;
    Value.UpdatedAt = Model->GetUpdatedAt() ? *Model->GetUpdatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzWalletPtr FGs2Money2WalletValueToEzWallet(
    const FGs2Money2WalletValue Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzWallet>()
        ->WithSlot(Model.Slot)
        ->WithSummary(FGs2Money2WalletSummaryToEzWalletSummary(Model.Summary))
        ->WithSharedFreeCurrency(Model.SharedFreeCurrency)
        ->WithUpdatedAt(Model.UpdatedAt);
}

UCLASS()
class BPGS2_API UGs2Money2WalletFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};