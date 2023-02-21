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
#include "Quest/Domain/Model/Gs2QuestEzQuestGroupModelDomain.h"
#include "Quest/Model/Gs2QuestQuestModel.h"
#include "Gs2QuestQuestGroupModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestQuestGroupModel
{
    GENERATED_BODY()

    Gs2::UE5::Quest::Domain::Model::FEzQuestGroupModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2QuestQuestGroupModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2QuestQuestModelValue> Quests = TArray<FGs2QuestQuestModelValue>();
    UPROPERTY(BlueprintReadOnly)
    FString ChallengePeriodEventId = "";
};

inline FGs2QuestQuestGroupModelValue EzQuestGroupModelToFGs2QuestQuestGroupModelValue(
    const Gs2::UE5::Quest::Model::FEzQuestGroupModelPtr Model
)
{
    FGs2QuestQuestGroupModelValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Quests = Model->GetQuests() ? [&]
    {
        TArray<FGs2QuestQuestModelValue> r;
        for (auto v : *Model->GetQuests())
        {
            r.Add(EzQuestModelToFGs2QuestQuestModelValue(v));
        }
        return r;
    }() : TArray<FGs2QuestQuestModelValue>();
    Value.ChallengePeriodEventId = Model->GetChallengePeriodEventId() ? *Model->GetChallengePeriodEventId() : "";
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzQuestGroupModelPtr FGs2QuestQuestGroupModelValueToEzQuestGroupModel(
    const FGs2QuestQuestGroupModelValue Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzQuestGroupModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithQuests([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzQuestModelPtr>>();
            for (auto v : Model.Quests) {
                r->Add(FGs2QuestQuestModelValueToEzQuestModel(v));
            }
            return r;
        }())
        ->WithChallengePeriodEventId(Model.ChallengePeriodEventId);
}

UCLASS()
class BPGS2_API UGs2QuestQuestGroupModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Quest::QuestModel", Category="Game Server Services|GS2-Quest|Namespace|QuestGroupModel|QuestModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="QuestModel") FGs2QuestQuestModel QuestModel(
        FGs2QuestQuestGroupModel QuestGroupModel,
        FString QuestName
    );
};