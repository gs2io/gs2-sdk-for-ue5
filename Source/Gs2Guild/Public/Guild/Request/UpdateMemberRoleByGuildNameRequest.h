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
#include "Dom/JsonObject.h"

namespace Gs2::Guild::Request
{
    class FUpdateMemberRoleByGuildNameRequest;

    class GS2GUILD_API FUpdateMemberRoleByGuildNameRequest final : public TSharedFromThis<FUpdateMemberRoleByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> RoleNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateMemberRoleByGuildNameRequest();
        FUpdateMemberRoleByGuildNameRequest(
            const FUpdateMemberRoleByGuildNameRequest& From
        );
        ~FUpdateMemberRoleByGuildNameRequest() = default;

        TSharedPtr<FUpdateMemberRoleByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMemberRoleByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMemberRoleByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FUpdateMemberRoleByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FUpdateMemberRoleByGuildNameRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FUpdateMemberRoleByGuildNameRequest> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FUpdateMemberRoleByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetRoleName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateMemberRoleByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMemberRoleByGuildNameRequest> FUpdateMemberRoleByGuildNameRequestPtr;
}