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
#include "Core/EzTransactionGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2CoreTransaction.generated.h"

USTRUCT(BlueprintType)
struct FGs2CoreOwnTransaction
{
    GENERATED_BODY()

    Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2CoreTransactionValue
{
    GENERATED_BODY()

    Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomainPtr Transaction;
};

inline FGs2CoreTransactionValue EzTransactionToFGs2CoreTransactionValue(
    const Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomainPtr Model
)
{
    FGs2CoreTransactionValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2CoreTransactionFunctionLibrary::EzTransactionToFGs2CoreTransactionValue] Model parameter specification is missing."))
        return Value;
    }
    return Value;
}

inline Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomainPtr FGs2CoreTransactionValueToEzTransaction(
    const FGs2CoreTransactionValue Model
)
{
    return Model.Transaction;
}

UCLASS()
class BPGS2_API UGs2CoreTransactionFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};