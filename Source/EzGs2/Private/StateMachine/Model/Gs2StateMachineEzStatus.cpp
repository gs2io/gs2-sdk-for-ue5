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

#include "EzGs2/Public/StateMachine/Model/Gs2StateMachineEzStatus.h"

namespace Gs2::UE5::StateMachine::Model
{

    TSharedPtr<FEzStatus> FEzStatus::WithStatusId(
        const TOptional<FString> StatusId
    )
    {
        this->StatusIdValue = StatusId;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithStacks(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzStackEntry>>> Stacks
    )
    {
        this->StacksValue = Stacks;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithVariables(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVariable>>> Variables
    )
    {
        this->VariablesValue = Variables;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithLastError(
        const TOptional<FString> LastError
    )
    {
        this->LastErrorValue = LastError;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithTransitionCount(
        const TOptional<int32> TransitionCount
    )
    {
        this->TransitionCountValue = TransitionCount;
        return SharedThis(this);
    }
    TOptional<FString> FEzStatus::GetStatusId() const
    {
        return StatusIdValue;
    }
    TOptional<FString> FEzStatus::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzStackEntry>>> FEzStatus::GetStacks() const
    {
        return StacksValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVariable>>> FEzStatus::GetVariables() const
    {
        return VariablesValue;
    }
    TOptional<FString> FEzStatus::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<FString> FEzStatus::GetLastError() const
    {
        return LastErrorValue;
    }
    TOptional<int32> FEzStatus::GetTransitionCount() const
    {
        return TransitionCountValue;
    }

    FString FEzStatus::GetTransitionCountString() const
    {
        if (!TransitionCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TransitionCountValue.GetValue());
    }

    Gs2::StateMachine::Model::FStatusPtr FEzStatus::ToModel() const
    {
        return MakeShared<Gs2::StateMachine::Model::FStatus>()
            ->WithStatusId(StatusIdValue)
            ->WithName(NameValue)
            ->WithStacks([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::StateMachine::Model::FStackEntry>>>();
                    if (StacksValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *StacksValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithVariables([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::StateMachine::Model::FVariable>>>();
                    if (VariablesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *VariablesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithStatus(StatusValue)
            ->WithLastError(LastErrorValue)
            ->WithTransitionCount(TransitionCountValue);
    }

    TSharedPtr<FEzStatus> FEzStatus::FromModel(const Gs2::StateMachine::Model::FStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStatus>()
            ->WithStatusId(Model->GetStatusId())
            ->WithName(Model->GetName())
            ->WithStacks([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzStackEntry>>>();
                    if (Model->GetStacks() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetStacks())
                    {
                        v->Add(FEzStackEntry::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithVariables([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzVariable>>>();
                    if (Model->GetVariables() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetVariables())
                    {
                        v->Add(FEzVariable::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithStatus(Model->GetStatus())
            ->WithLastError(Model->GetLastError())
            ->WithTransitionCount(Model->GetTransitionCount());
    }
}