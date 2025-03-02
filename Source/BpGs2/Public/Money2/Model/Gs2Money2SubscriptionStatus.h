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
#include "Money2/Domain/Model/Gs2Money2EzSubscriptionStatusGameSessionDomain.h"
#include "Money2/Model/Gs2Money2SubscribeTransaction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2Money2SubscriptionStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2OwnSubscriptionStatus
{
    GENERATED_BODY()

    Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2Money2SubscriptionStatusValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ContentName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Status = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ExpiresAt = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2Money2SubscribeTransaction> Detail = TArray<FGs2Money2SubscribeTransaction>();
};

inline FGs2Money2SubscriptionStatusValue EzSubscriptionStatusToFGs2Money2SubscriptionStatusValue(
    const Gs2::UE5::Money2::Model::FEzSubscriptionStatusPtr Model
)
{
    FGs2Money2SubscriptionStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2SubscriptionStatusFunctionLibrary::EzSubscriptionStatusToFGs2Money2SubscriptionStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.ContentName = Model->GetContentName() ? *Model->GetContentName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Status = Model->GetStatus() ? *Model->GetStatus() : "";
    Value.ExpiresAt = Model->GetExpiresAt() ? *Model->GetExpiresAt() : 0;
    Value.Detail = Model->GetDetail() ? [&]
    {
        TArray<FGs2Money2SubscribeTransaction> r;
        for (auto v : *Model->GetDetail())
        {
            r.Add(EzSubscribeTransactionToFGs2Money2SubscribeTransaction(v));
        }
        return r;
    }() : TArray<FGs2Money2SubscribeTransaction>();
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzSubscriptionStatusPtr FGs2Money2SubscriptionStatusValueToEzSubscriptionStatus(
    const FGs2Money2SubscriptionStatusValue Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzSubscriptionStatus>()
        ->WithContentName(Model.ContentName)
        ->WithUserId(Model.UserId)
        ->WithStatus(Model.Status)
        ->WithExpiresAt(Model.ExpiresAt)
        ->WithDetail([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Money2::Model::FEzSubscribeTransactionPtr>>();
            for (auto v : Model.Detail) {
                r->Add(FGs2Money2SubscribeTransactionToEzSubscribeTransaction(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2Money2SubscriptionStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};