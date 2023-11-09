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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"

#include "Idle/Model/Gs2IdleEzAcquireActionList.h"
#include "Idle/Model/Gs2IdleAcquireAction.h"
#include "Gs2IdleAcquireActionList.generated.h"

USTRUCT(BlueprintType)
struct FGs2IdleAcquireActionList
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2IdleAcquireAction> AcquireActions = TArray<FGs2IdleAcquireAction>();
};

inline FGs2IdleAcquireActionList EzAcquireActionListToFGs2IdleAcquireActionList(
    const Gs2::UE5::Idle::Model::FEzAcquireActionListPtr Model
)
{
    FGs2IdleAcquireActionList Value;
    Value.AcquireActions = Model->GetAcquireActions() ? [&]
    {
        TArray<FGs2IdleAcquireAction> r;
        for (auto v : *Model->GetAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2IdleAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2IdleAcquireAction>();
    return Value;
}

inline Gs2::UE5::Idle::Model::FEzAcquireActionListPtr FGs2IdleAcquireActionListToEzAcquireActionList(
    const FGs2IdleAcquireActionList Model
)
{
    return MakeShared<Gs2::UE5::Idle::Model::FEzAcquireActionList>()
        ->WithAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Idle::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.AcquireActions) {
                r->Add(FGs2IdleAcquireActionToEzAcquireAction(v));
            }
            return r;
        }());
}