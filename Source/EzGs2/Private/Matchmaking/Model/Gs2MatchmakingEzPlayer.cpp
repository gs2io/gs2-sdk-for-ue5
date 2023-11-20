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

#include "Matchmaking/Model/Gs2MatchmakingEzPlayer.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzPlayer> FEzPlayer::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlayer> FEzPlayer::WithAttributes(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttribute>>> Attributes
    )
    {
        this->AttributesValue = Attributes;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlayer> FEzPlayer::WithRoleName(
        const TOptional<FString> RoleName
    )
    {
        this->RoleNameValue = RoleName;
        return SharedThis(this);
    }

    TSharedPtr<FEzPlayer> FEzPlayer::WithDenyUserIds(
        const TSharedPtr<TArray<FString>> DenyUserIds
    )
    {
        this->DenyUserIdsValue = DenyUserIds;
        return SharedThis(this);
    }
    TOptional<FString> FEzPlayer::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttribute>>> FEzPlayer::GetAttributes() const
    {
        return AttributesValue;
    }
    TOptional<FString> FEzPlayer::GetRoleName() const
    {
        return RoleNameValue;
    }
    TSharedPtr<TArray<FString>> FEzPlayer::GetDenyUserIds() const
    {
        return DenyUserIdsValue;
    }

    Gs2::Matchmaking::Model::FPlayerPtr FEzPlayer::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FPlayer>()
            ->WithUserId(UserIdValue)
            ->WithAttributes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Matchmaking::Model::FAttribute>>>();
                    if (AttributesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AttributesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithRoleName(RoleNameValue)
            ->WithDenyUserIds(DenyUserIdsValue);
    }

    TSharedPtr<FEzPlayer> FEzPlayer::FromModel(const Gs2::Matchmaking::Model::FPlayerPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPlayer>()
            ->WithUserId(Model->GetUserId())
            ->WithAttributes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAttribute>>>();
                    if (Model->GetAttributes() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAttributes())
                    {
                        v->Add(FEzAttribute::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithRoleName(Model->GetRoleName())
            ->WithDenyUserIds(Model->GetDenyUserIds());
    }
}