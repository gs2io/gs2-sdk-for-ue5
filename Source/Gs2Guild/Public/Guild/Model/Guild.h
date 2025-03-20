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
#include "RoleModel.h"
#include "Member.h"

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FGuild final : public FGs2Object, public TSharedFromThis<FGuild>
    {
        TOptional<FString> GuildIdValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DisplayNameValue;
        TOptional<int32> Attribute1Value;
        TOptional<int32> Attribute2Value;
        TOptional<int32> Attribute3Value;
        TOptional<int32> Attribute4Value;
        TOptional<int32> Attribute5Value;
        TOptional<FString> MetadataValue;
        TOptional<FString> JoinPolicyValue;
        TSharedPtr<TArray<TSharedPtr<FRoleModel>>> CustomRolesValue;
        TOptional<FString> GuildMemberDefaultRoleValue;
        TOptional<int32> CurrentMaximumMemberCountValue;
        TSharedPtr<TArray<TSharedPtr<FMember>>> MembersValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FGuild();
        FGuild(
            const FGuild& From
        );
        virtual ~FGuild() override = default;

        TSharedPtr<FGuild> WithGuildId(const TOptional<FString> GuildId);
        TSharedPtr<FGuild> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FGuild> WithName(const TOptional<FString> Name);
        TSharedPtr<FGuild> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FGuild> WithAttribute1(const TOptional<int32> Attribute1);
        TSharedPtr<FGuild> WithAttribute2(const TOptional<int32> Attribute2);
        TSharedPtr<FGuild> WithAttribute3(const TOptional<int32> Attribute3);
        TSharedPtr<FGuild> WithAttribute4(const TOptional<int32> Attribute4);
        TSharedPtr<FGuild> WithAttribute5(const TOptional<int32> Attribute5);
        TSharedPtr<FGuild> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGuild> WithJoinPolicy(const TOptional<FString> JoinPolicy);
        TSharedPtr<FGuild> WithCustomRoles(const TSharedPtr<TArray<TSharedPtr<FRoleModel>>> CustomRoles);
        TSharedPtr<FGuild> WithGuildMemberDefaultRole(const TOptional<FString> GuildMemberDefaultRole);
        TSharedPtr<FGuild> WithCurrentMaximumMemberCount(const TOptional<int32> CurrentMaximumMemberCount);
        TSharedPtr<FGuild> WithMembers(const TSharedPtr<TArray<TSharedPtr<FMember>>> Members);
        TSharedPtr<FGuild> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGuild> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FGuild> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetGuildId() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDisplayName() const;
        TOptional<int32> GetAttribute1() const;
        FString GetAttribute1String() const;
        TOptional<int32> GetAttribute2() const;
        FString GetAttribute2String() const;
        TOptional<int32> GetAttribute3() const;
        FString GetAttribute3String() const;
        TOptional<int32> GetAttribute4() const;
        FString GetAttribute4String() const;
        TOptional<int32> GetAttribute5() const;
        FString GetAttribute5String() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetJoinPolicy() const;
        TSharedPtr<TArray<TSharedPtr<FRoleModel>>> GetCustomRoles() const;
        TOptional<FString> GetGuildMemberDefaultRole() const;
        TOptional<int32> GetCurrentMaximumMemberCount() const;
        FString GetCurrentMaximumMemberCountString() const;
        TSharedPtr<TArray<TSharedPtr<FMember>>> GetMembers() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildNameFromGrn(const FString Grn);

        static TSharedPtr<FGuild> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGuild, ESPMode::ThreadSafe> FGuildPtr;
}