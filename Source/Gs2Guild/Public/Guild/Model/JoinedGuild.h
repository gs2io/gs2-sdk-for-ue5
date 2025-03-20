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

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FJoinedGuild final : public FGs2Object, public TSharedFromThis<FJoinedGuild>
    {
        TOptional<FString> JoinedGuildIdValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> CreatedAtValue;

    public:
        FJoinedGuild();
        FJoinedGuild(
            const FJoinedGuild& From
        );
        virtual ~FJoinedGuild() override = default;

        TSharedPtr<FJoinedGuild> WithJoinedGuildId(const TOptional<FString> JoinedGuildId);
        TSharedPtr<FJoinedGuild> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FJoinedGuild> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FJoinedGuild> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FJoinedGuild> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetJoinedGuildId() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetGuildModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildNameFromGrn(const FString Grn);

        static TSharedPtr<FJoinedGuild> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FJoinedGuild, ESPMode::ThreadSafe> FJoinedGuildPtr;
}