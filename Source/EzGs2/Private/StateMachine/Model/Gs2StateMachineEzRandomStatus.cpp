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

#include "StateMachine/Model/Gs2StateMachineEzRandomStatus.h"

namespace Gs2::UE5::StateMachine::Model
{

    TSharedPtr<FEzRandomStatus> FEzRandomStatus::WithSeed(
        const TOptional<int64> Seed
    )
    {
        this->SeedValue = Seed;
        return SharedThis(this);
    }

    TSharedPtr<FEzRandomStatus> FEzRandomStatus::WithUsed(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomUsed>>> Used
    )
    {
        this->UsedValue = Used;
        return SharedThis(this);
    }
    TOptional<int64> FEzRandomStatus::GetSeed() const
    {
        return SeedValue;
    }

    FString FEzRandomStatus::GetSeedString() const
    {
        if (!SeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeedValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzRandomUsed>>> FEzRandomStatus::GetUsed() const
    {
        return UsedValue;
    }

    Gs2::StateMachine::Model::FRandomStatusPtr FEzRandomStatus::ToModel() const
    {
        return MakeShared<Gs2::StateMachine::Model::FRandomStatus>()
            ->WithSeed(SeedValue)
            ->WithUsed([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::StateMachine::Model::FRandomUsed>>>();
                    if (UsedValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *UsedValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzRandomStatus> FEzRandomStatus::FromModel(const Gs2::StateMachine::Model::FRandomStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRandomStatus>()
            ->WithSeed(Model->GetSeed())
            ->WithUsed([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzRandomUsed>>>();
                    if (Model->GetUsed() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetUsed())
                    {
                        v->Add(FEzRandomUsed::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}