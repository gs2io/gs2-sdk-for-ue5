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
    class FUpdateMemberRoleRequest;

    class GS2GUILD_API FUpdateMemberRoleRequest final : public TSharedFromThis<FUpdateMemberRoleRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> RoleNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateMemberRoleRequest();
        FUpdateMemberRoleRequest(
            const FUpdateMemberRoleRequest& From
        );
        ~FUpdateMemberRoleRequest() = default;

        TSharedPtr<FUpdateMemberRoleRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMemberRoleRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMemberRoleRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FUpdateMemberRoleRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateMemberRoleRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FUpdateMemberRoleRequest> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FUpdateMemberRoleRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetRoleName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateMemberRoleRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMemberRoleRequest> FUpdateMemberRoleRequestPtr;
}