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

#include "Quest/Model/Gs2QuestEzContents.h"
#include "Quest/Model/Gs2QuestAcquireAction.h"
#include "Gs2QuestContents.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestContents
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2QuestAcquireAction> CompleteAcquireActions = TArray<FGs2QuestAcquireAction>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Weight = 0;
};

inline FGs2QuestContents EzContentsToFGs2QuestContents(
    const Gs2::UE5::Quest::Model::FEzContentsPtr Model
)
{
    FGs2QuestContents Value;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.CompleteAcquireActions = Model->GetCompleteAcquireActions() ? [&]
    {
        TArray<FGs2QuestAcquireAction> r;
        for (auto v : *Model->GetCompleteAcquireActions())
        {r.Add(EzAcquireActionToFGs2QuestAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2QuestAcquireAction>();
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzContentsPtr FGs2QuestContentsToEzContents(
    const FGs2QuestContents Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzContents>()
        ->WithMetadata(Model.Metadata)
        ->WithCompleteAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.CompleteAcquireActions) {
                r->Add(FGs2QuestAcquireActionToEzAcquireAction(v));
            }
            return r;
        }());
}