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

#include "EzGs2/Public/Matchmaking/Model/Gs2MatchmakingEzCapacityOfRole.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzCapacityOfRole> FEzCapacityOfRole::WithRoleName(
        const TOptional<FString> RoleName
    )
    {
        this->RoleNameValue = RoleName;
        return SharedThis(this);
    }

    TSharedPtr<FEzCapacityOfRole> FEzCapacityOfRole::WithRoleAliases(
        const TSharedPtr<TArray<FString>> RoleAliases
    )
    {
        this->RoleAliasesValue = RoleAliases;
        return SharedThis(this);
    }

    TSharedPtr<FEzCapacityOfRole> FEzCapacityOfRole::WithCapacity(
        const TOptional<int32> Capacity
    )
    {
        this->CapacityValue = Capacity;
        return SharedThis(this);
    }

    TSharedPtr<FEzCapacityOfRole> FEzCapacityOfRole::WithParticipants(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzPlayer>>> Participants
    )
    {
        this->ParticipantsValue = Participants;
        return SharedThis(this);
    }
    TOptional<FString> FEzCapacityOfRole::GetRoleName() const
    {
        return RoleNameValue;
    }
    TSharedPtr<TArray<FString>> FEzCapacityOfRole::GetRoleAliases() const
    {
        return RoleAliasesValue;
    }
    TOptional<int32> FEzCapacityOfRole::GetCapacity() const
    {
        return CapacityValue;
    }

    FString FEzCapacityOfRole::GetCapacityString() const
    {
        if (!CapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), CapacityValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzPlayer>>> FEzCapacityOfRole::GetParticipants() const
    {
        return ParticipantsValue;
    }

    Gs2::Matchmaking::Model::FCapacityOfRolePtr FEzCapacityOfRole::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FCapacityOfRole>()
            ->WithRoleName(RoleNameValue)
            ->WithRoleAliases(RoleAliasesValue)
            ->WithCapacity(CapacityValue)
            ->WithParticipants([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FPlayer>>>();
                    if (ParticipantsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ParticipantsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzCapacityOfRole> FEzCapacityOfRole::FromModel(const Gs2::Matchmaking::Model::FCapacityOfRolePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCapacityOfRole>()
            ->WithRoleName(Model->GetRoleName())
            ->WithRoleAliases(Model->GetRoleAliases())
            ->WithCapacity(Model->GetCapacity())
            ->WithParticipants([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzPlayer>>>();
                    if (Model->GetParticipants() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetParticipants())
                    {
                        v->Add(FEzPlayer::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}