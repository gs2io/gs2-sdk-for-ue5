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

#include "Account/Model/Gs2AccountEzBanStatus.h"
#include "Gs2AccountBanStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2AccountBanStatus
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Reason = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 ReleaseTimestamp = 0;
};

inline FGs2AccountBanStatus EzBanStatusToFGs2AccountBanStatus(
    const Gs2::UE5::Account::Model::FEzBanStatusPtr Model
)
{
    FGs2AccountBanStatus Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Reason = Model->GetReason() ? *Model->GetReason() : "";
    Value.ReleaseTimestamp = Model->GetReleaseTimestamp() ? *Model->GetReleaseTimestamp() : 0;
    return Value;
}

inline Gs2::UE5::Account::Model::FEzBanStatusPtr FGs2AccountBanStatusToEzBanStatus(
    const FGs2AccountBanStatus Model
)
{
    return MakeShared<Gs2::UE5::Account::Model::FEzBanStatus>()
        ->WithName(Model.Name)
        ->WithReason(Model.Reason)
        ->WithReleaseTimestamp(Model.ReleaseTimestamp);
}