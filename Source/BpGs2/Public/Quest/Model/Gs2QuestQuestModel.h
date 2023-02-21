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
#include "Quest/Domain/Model/Gs2QuestEzQuestModelDomain.h"
#include "Quest/Model/Gs2QuestContents.h"
#include "Quest/Model/Gs2QuestAcquireAction.h"
#include "Quest/Model/Gs2QuestConsumeAction.h"
#include "Quest/Model/Gs2QuestAcquireAction.h"
#include "Gs2QuestQuestModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestQuestModel
{
    GENERATED_BODY()

    Gs2::UE5::Quest::Domain::Model::FEzQuestModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2QuestQuestModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString QuestModelId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2QuestContents> Contents = TArray<FGs2QuestContents>();
    UPROPERTY(BlueprintReadOnly)
    FString ChallengePeriodEventId = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2QuestAcquireAction> FirstCompleteAcquireActions = TArray<FGs2QuestAcquireAction>();
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2QuestConsumeAction> ConsumeActions = TArray<FGs2QuestConsumeAction>();
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2QuestAcquireAction> FailedAcquireActions = TArray<FGs2QuestAcquireAction>();
    UPROPERTY(BlueprintReadOnly)
    TArray<FString> PremiseQuestNames = TArray<FString>();
};

inline FGs2QuestQuestModelValue EzQuestModelToFGs2QuestQuestModelValue(
    const Gs2::UE5::Quest::Model::FEzQuestModelPtr Model
)
{
    FGs2QuestQuestModelValue Value;
    Value.QuestModelId = Model->GetQuestModelId() ? *Model->GetQuestModelId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Contents = Model->GetContents() ? [&]
    {
        TArray<FGs2QuestContents> r;
        for (auto v : *Model->GetContents())
        {
            r.Add(EzContentsToFGs2QuestContents(v));
        }
        return r;
    }() : TArray<FGs2QuestContents>();
    Value.ChallengePeriodEventId = Model->GetChallengePeriodEventId() ? *Model->GetChallengePeriodEventId() : "";
    Value.FirstCompleteAcquireActions = Model->GetFirstCompleteAcquireActions() ? [&]
    {
        TArray<FGs2QuestAcquireAction> r;
        for (auto v : *Model->GetFirstCompleteAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2QuestAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2QuestAcquireAction>();
    Value.ConsumeActions = Model->GetConsumeActions() ? [&]
    {
        TArray<FGs2QuestConsumeAction> r;
        for (auto v : *Model->GetConsumeActions())
        {
            r.Add(EzConsumeActionToFGs2QuestConsumeAction(v));
        }
        return r;
    }() : TArray<FGs2QuestConsumeAction>();
    Value.FailedAcquireActions = Model->GetFailedAcquireActions() ? [&]
    {
        TArray<FGs2QuestAcquireAction> r;
        for (auto v : *Model->GetFailedAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2QuestAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2QuestAcquireAction>();
    Value.PremiseQuestNames = Model->GetPremiseQuestNames() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetPremiseQuestNames())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzQuestModelPtr FGs2QuestQuestModelValueToEzQuestModel(
    const FGs2QuestQuestModelValue Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzQuestModel>()
        ->WithQuestModelId(Model.QuestModelId)
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithContents([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzContentsPtr>>();
            for (auto v : Model.Contents) {
                r->Add(FGs2QuestContentsToEzContents(v));
            }
            return r;
        }())
        ->WithChallengePeriodEventId(Model.ChallengePeriodEventId)
        ->WithFirstCompleteAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.FirstCompleteAcquireActions) {
                r->Add(FGs2QuestAcquireActionToEzAcquireAction(v));
            }
            return r;
        }())
        ->WithConsumeActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzConsumeActionPtr>>();
            for (auto v : Model.ConsumeActions) {
                r->Add(FGs2QuestConsumeActionToEzConsumeAction(v));
            }
            return r;
        }())
        ->WithFailedAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.FailedAcquireActions) {
                r->Add(FGs2QuestAcquireActionToEzAcquireAction(v));
            }
            return r;
        }())
        ->WithPremiseQuestNames([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.PremiseQuestNames) {
                r->Add(v);
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2QuestQuestModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};