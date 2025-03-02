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

#include "Money2/Model/Gs2Money2EzSubscribeTransaction.h"
#include "Gs2Money2SubscribeTransaction.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2SubscribeTransaction
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ContentName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Store = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString StatusDetail = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 ExpiresAt = 0;
};

inline FGs2Money2SubscribeTransaction EzSubscribeTransactionToFGs2Money2SubscribeTransaction(
    const Gs2::UE5::Money2::Model::FEzSubscribeTransactionPtr Model
)
{
    FGs2Money2SubscribeTransaction Value;
    Value.ContentName = Model->GetContentName() ? *Model->GetContentName() : "";
    Value.Store = Model->GetStore() ? *Model->GetStore() : "";
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.StatusDetail = Model->GetStatusDetail() ? *Model->GetStatusDetail() : "";
    Value.ExpiresAt = Model->GetExpiresAt() ? *Model->GetExpiresAt() : 0;
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzSubscribeTransactionPtr FGs2Money2SubscribeTransactionToEzSubscribeTransaction(
    const FGs2Money2SubscribeTransaction Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzSubscribeTransaction>()
        ->WithContentName(Model.ContentName)
        ->WithStore(Model.Store)
        ->WithTransactionId(Model.TransactionId)
        ->WithStatusDetail(Model.StatusDetail)
        ->WithExpiresAt(Model.ExpiresAt);
}