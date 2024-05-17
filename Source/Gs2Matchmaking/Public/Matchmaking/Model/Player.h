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
#include "Attribute.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FPlayer final : public Gs2Object, public TSharedFromThis<FPlayer>
    {
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<FAttribute>>> AttributesValue;
        TOptional<FString> RoleNameValue;
        TSharedPtr<TArray<FString>> DenyUserIdsValue;
        TOptional<int64> CreatedAtValue;

    public:
        FPlayer();
        FPlayer(
            const FPlayer& From
        );
        virtual ~FPlayer() override = default;

        TSharedPtr<FPlayer> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPlayer> WithAttributes(const TSharedPtr<TArray<TSharedPtr<FAttribute>>> Attributes);
        TSharedPtr<FPlayer> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FPlayer> WithDenyUserIds(const TSharedPtr<TArray<FString>> DenyUserIds);
        TSharedPtr<FPlayer> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<TSharedPtr<FAttribute>>> GetAttributes() const;
        TOptional<FString> GetRoleName() const;
        TSharedPtr<TArray<FString>> GetDenyUserIds() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;


        static TSharedPtr<FPlayer> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPlayer, ESPMode::ThreadSafe> FPlayerPtr;
}