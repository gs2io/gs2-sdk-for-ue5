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
#include "Core/Gs2Object.h"
#include "Player.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FCapacityOfRole final : public Gs2Object, public TSharedFromThis<FCapacityOfRole>
    {
        TOptional<FString> RoleNameValue;
        TSharedPtr<TArray<FString>> RoleAliasesValue;
        TOptional<int32> CapacityValue;
        TSharedPtr<TArray<TSharedPtr<FPlayer>>> ParticipantsValue;

    public:
        FCapacityOfRole();
        FCapacityOfRole(
            const FCapacityOfRole& From
        );
        virtual ~FCapacityOfRole() override = default;

        TSharedPtr<FCapacityOfRole> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FCapacityOfRole> WithRoleAliases(const TSharedPtr<TArray<FString>> RoleAliases);
        TSharedPtr<FCapacityOfRole> WithCapacity(const TOptional<int32> Capacity);
        TSharedPtr<FCapacityOfRole> WithParticipants(const TSharedPtr<TArray<TSharedPtr<FPlayer>>> Participants);

        TOptional<FString> GetRoleName() const;
        TSharedPtr<TArray<FString>> GetRoleAliases() const;
        TOptional<int32> GetCapacity() const;
        FString GetCapacityString() const;
        TSharedPtr<TArray<TSharedPtr<FPlayer>>> GetParticipants() const;


        static TSharedPtr<FCapacityOfRole> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCapacityOfRole, ESPMode::ThreadSafe> FCapacityOfRolePtr;
}