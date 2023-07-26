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
#include "StateMachine/Domain/Model/Gs2StateMachineEzStatusGameSessionDomain.h"
#include "StateMachine/Model/Gs2StateMachineStackEntry.h"
#include "StateMachine/Model/Gs2StateMachineVariable.h"
#include "Core/BpGs2Constant.h"
#include "Gs2StateMachineStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineOwnStatus
{
    GENERATED_BODY()

    Gs2::UE5::StateMachine::Domain::Model::FEzStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2StateMachineStatusValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString StatusId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2StateMachineStackEntry> Stacks = TArray<FGs2StateMachineStackEntry>();
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2StateMachineVariable> Variables = TArray<FGs2StateMachineVariable>();
    UPROPERTY(BlueprintReadOnly)
    FString Status = "";
    UPROPERTY(BlueprintReadOnly)
    FString LastError = "";
    UPROPERTY(BlueprintReadOnly)
    int32 TransitionCount = 0;
};

inline FGs2StateMachineStatusValue EzStatusToFGs2StateMachineStatusValue(
    const Gs2::UE5::StateMachine::Model::FEzStatusPtr Model
)
{
    FGs2StateMachineStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StateMachineStatusFunctionLibrary::EzStatusToFGs2StateMachineStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.StatusId = Model->GetStatusId() ? *Model->GetStatusId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Stacks = Model->GetStacks() ? [&]
    {
        TArray<FGs2StateMachineStackEntry> r;
        for (auto v : *Model->GetStacks())
        {
            r.Add(EzStackEntryToFGs2StateMachineStackEntry(v));
        }
        return r;
    }() : TArray<FGs2StateMachineStackEntry>();
    Value.Variables = Model->GetVariables() ? [&]
    {
        TArray<FGs2StateMachineVariable> r;
        for (auto v : *Model->GetVariables())
        {
            r.Add(EzVariableToFGs2StateMachineVariable(v));
        }
        return r;
    }() : TArray<FGs2StateMachineVariable>();
    Value.Status = Model->GetStatus() ? *Model->GetStatus() : "";
    Value.LastError = Model->GetLastError() ? *Model->GetLastError() : "";
    Value.TransitionCount = Model->GetTransitionCount() ? *Model->GetTransitionCount() : 0;
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzStatusPtr FGs2StateMachineStatusValueToEzStatus(
    const FGs2StateMachineStatusValue Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzStatus>()
        ->WithStatusId(Model.StatusId)
        ->WithName(Model.Name)
        ->WithStacks([&]{
            auto r = MakeShared<TArray<Gs2::UE5::StateMachine::Model::FEzStackEntryPtr>>();
            for (auto v : Model.Stacks) {
                r->Add(FGs2StateMachineStackEntryToEzStackEntry(v));
            }
            return r;
        }())
        ->WithVariables([&]{
            auto r = MakeShared<TArray<Gs2::UE5::StateMachine::Model::FEzVariablePtr>>();
            for (auto v : Model.Variables) {
                r->Add(FGs2StateMachineVariableToEzVariable(v));
            }
            return r;
        }())
        ->WithStatus(Model.Status)
        ->WithLastError(Model.LastError)
        ->WithTransitionCount(Model.TransitionCount);
}

UCLASS()
class BPGS2_API UGs2StateMachineStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};