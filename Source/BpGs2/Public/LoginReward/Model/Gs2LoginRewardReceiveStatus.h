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
#include "LoginReward/Domain/Model/Gs2LoginRewardEzReceiveStatusGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2LoginRewardReceiveStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2LoginRewardOwnReceiveStatus
{
    GENERATED_BODY()

    Gs2::UE5::LoginReward::Domain::Model::FEzReceiveStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2LoginRewardReceiveStatusValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString BonusModelName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<bool> ReceivedSteps = TArray<bool>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 LastReceivedAt = 0;
};

inline FGs2LoginRewardReceiveStatusValue EzReceiveStatusToFGs2LoginRewardReceiveStatusValue(
    const Gs2::UE5::LoginReward::Model::FEzReceiveStatusPtr Model
)
{
    FGs2LoginRewardReceiveStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardReceiveStatusFunctionLibrary::EzReceiveStatusToFGs2LoginRewardReceiveStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.BonusModelName = Model->GetBonusModelName() ? *Model->GetBonusModelName() : "";
    Value.ReceivedSteps = Model->GetReceivedSteps() ? [&]
    {
        TArray<bool> r;
        for (auto v : *Model->GetReceivedSteps())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<bool>();
    Value.LastReceivedAt = Model->GetLastReceivedAt() ? *Model->GetLastReceivedAt() : 0;
    return Value;
}

inline Gs2::UE5::LoginReward::Model::FEzReceiveStatusPtr FGs2LoginRewardReceiveStatusValueToEzReceiveStatus(
    const FGs2LoginRewardReceiveStatusValue Model
)
{
    return MakeShared<Gs2::UE5::LoginReward::Model::FEzReceiveStatus>()
        ->WithBonusModelName(Model.BonusModelName)
        ->WithReceivedSteps([&]{
            auto r = MakeShared<TArray<bool>>();
            for (auto v : Model.ReceivedSteps) {
                r->Add(v);
            }
            return r;
        }())
        ->WithLastReceivedAt(Model.LastReceivedAt);
}

UCLASS()
class BPGS2_API UGs2LoginRewardReceiveStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};