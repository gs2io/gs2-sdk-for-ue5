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
#include "Quest/Domain/Model/Gs2QuestEzCompletedQuestListGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2QuestCompletedQuestList.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestOwnCompletedQuestList
{
    GENERATED_BODY()

    Gs2::UE5::Quest::Domain::Model::FEzCompletedQuestListGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2QuestCompletedQuestListValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString QuestGroupName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FString> CompleteQuestNames = TArray<FString>();
};

inline FGs2QuestCompletedQuestListValue EzCompletedQuestListToFGs2QuestCompletedQuestListValue(
    const Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr Model
)
{
    FGs2QuestCompletedQuestListValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestCompletedQuestListFunctionLibrary::EzCompletedQuestListToFGs2QuestCompletedQuestListValue] Model parameter specification is missing."))
        return Value;
    }
    Value.QuestGroupName = Model->GetQuestGroupName() ? *Model->GetQuestGroupName() : "";
    Value.CompleteQuestNames = Model->GetCompleteQuestNames() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetCompleteQuestNames())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr FGs2QuestCompletedQuestListValueToEzCompletedQuestList(
    const FGs2QuestCompletedQuestListValue Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzCompletedQuestList>()
        ->WithQuestGroupName(Model.QuestGroupName)
        ->WithCompleteQuestNames([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.CompleteQuestNames) {
                r->Add(v);
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2QuestCompletedQuestListFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};