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
#include "Matchmaking/Model/CapacityOfRole.h"
#include "Gs2MatchmakingEzPlayer.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzCapacityOfRole final : public TSharedFromThis<FEzCapacityOfRole>
	{
        TOptional<FString> RoleNameValue;
        TSharedPtr<TArray<FString>> RoleAliasesValue;
        TOptional<int32> CapacityValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzPlayer>>> ParticipantsValue;

	public:
        TSharedPtr<FEzCapacityOfRole> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FEzCapacityOfRole> WithRoleAliases(const TSharedPtr<TArray<FString>> RoleAliases);
        TSharedPtr<FEzCapacityOfRole> WithCapacity(const TOptional<int32> Capacity);
        TSharedPtr<FEzCapacityOfRole> WithParticipants(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzPlayer>>> Participants);

        TOptional<FString> GetRoleName() const;

        TSharedPtr<TArray<FString>> GetRoleAliases() const;

        TOptional<int32> GetCapacity() const;
        FString GetCapacityString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzPlayer>>> GetParticipants() const;

        Gs2::Matchmaking::Model::FCapacityOfRolePtr ToModel() const;
        static TSharedPtr<FEzCapacityOfRole> FromModel(Gs2::Matchmaking::Model::FCapacityOfRolePtr Model);
    };
    typedef TSharedPtr<FEzCapacityOfRole> FEzCapacityOfRolePtr;
}