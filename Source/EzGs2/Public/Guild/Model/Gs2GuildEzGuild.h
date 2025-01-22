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
#include "Guild/Model/Guild.h"
#include "Gs2GuildEzRoleModel.h"
#include "Gs2GuildEzMember.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzGuild final : public TSharedFromThis<FEzGuild>
	{
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
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRolesValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzMember>>> MembersValue;

	public:
        TSharedPtr<FEzGuild> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FEzGuild> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzGuild> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FEzGuild> WithAttribute1(const TOptional<int32> Attribute1);
        TSharedPtr<FEzGuild> WithAttribute2(const TOptional<int32> Attribute2);
        TSharedPtr<FEzGuild> WithAttribute3(const TOptional<int32> Attribute3);
        TSharedPtr<FEzGuild> WithAttribute4(const TOptional<int32> Attribute4);
        TSharedPtr<FEzGuild> WithAttribute5(const TOptional<int32> Attribute5);
        TSharedPtr<FEzGuild> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzGuild> WithJoinPolicy(const TOptional<FString> JoinPolicy);
        TSharedPtr<FEzGuild> WithCustomRoles(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles);
        TSharedPtr<FEzGuild> WithMembers(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzMember>>> Members);

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

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> GetCustomRoles() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzMember>>> GetMembers() const;

        Gs2::Guild::Model::FGuildPtr ToModel() const;
        static TSharedPtr<FEzGuild> FromModel(Gs2::Guild::Model::FGuildPtr Model);
    };
    typedef TSharedPtr<FEzGuild> FEzGuildPtr;
}