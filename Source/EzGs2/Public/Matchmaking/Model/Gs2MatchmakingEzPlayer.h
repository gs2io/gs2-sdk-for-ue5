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
#include "Matchmaking/Model/Player.h"
#include "Gs2MatchmakingEzAttribute.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzPlayer final : public TSharedFromThis<FEzPlayer>
	{
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttribute>>> AttributesValue;
        TOptional<FString> RoleNameValue;
        TSharedPtr<TArray<FString>> DenyUserIdsValue;

	public:
        TSharedPtr<FEzPlayer> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzPlayer> WithAttributes(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttribute>>> Attributes);
        TSharedPtr<FEzPlayer> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FEzPlayer> WithDenyUserIds(const TSharedPtr<TArray<FString>> DenyUserIds);

        TOptional<FString> GetUserId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttribute>>> GetAttributes() const;

        TOptional<FString> GetRoleName() const;

        TSharedPtr<TArray<FString>> GetDenyUserIds() const;

        Gs2::Matchmaking::Model::FPlayerPtr ToModel() const;
        static TSharedPtr<FEzPlayer> FromModel(Gs2::Matchmaking::Model::FPlayerPtr Model);
    };
    typedef TSharedPtr<FEzPlayer> FEzPlayerPtr;
}