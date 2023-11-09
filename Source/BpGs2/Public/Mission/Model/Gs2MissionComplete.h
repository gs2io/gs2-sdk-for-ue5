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
#include "Mission/Domain/Model/Gs2MissionEzCompleteGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MissionComplete.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionOwnComplete
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MissionCompleteValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString MissionGroupName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FString> CompletedMissionTaskNames = TArray<FString>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FString> ReceivedMissionTaskNames = TArray<FString>();
};

inline FGs2MissionCompleteValue EzCompleteToFGs2MissionCompleteValue(
    const Gs2::UE5::Mission::Model::FEzCompletePtr Model
)
{
    FGs2MissionCompleteValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionCompleteFunctionLibrary::EzCompleteToFGs2MissionCompleteValue] Model parameter specification is missing."))
        return Value;
    }
    Value.MissionGroupName = Model->GetMissionGroupName() ? *Model->GetMissionGroupName() : "";
    Value.CompletedMissionTaskNames = Model->GetCompletedMissionTaskNames() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetCompletedMissionTaskNames())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    Value.ReceivedMissionTaskNames = Model->GetReceivedMissionTaskNames() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetReceivedMissionTaskNames())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzCompletePtr FGs2MissionCompleteValueToEzComplete(
    const FGs2MissionCompleteValue Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzComplete>()
        ->WithMissionGroupName(Model.MissionGroupName)
        ->WithCompletedMissionTaskNames([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.CompletedMissionTaskNames) {
                r->Add(v);
            }
            return r;
        }())
        ->WithReceivedMissionTaskNames([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.ReceivedMissionTaskNames) {
                r->Add(v);
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2MissionCompleteFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};