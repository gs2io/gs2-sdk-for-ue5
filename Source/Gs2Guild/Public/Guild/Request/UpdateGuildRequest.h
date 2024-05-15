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
#include "../Model/RoleModel.h"

namespace Gs2::Guild::Request
{
    class FUpdateGuildRequest;

    class GS2GUILD_API FUpdateGuildRequest final : public TSharedFromThis<FUpdateGuildRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> DisplayNameValue;
        TOptional<int32> Attribute1Value;
        TOptional<int32> Attribute2Value;
        TOptional<int32> Attribute3Value;
        TOptional<int32> Attribute4Value;
        TOptional<int32> Attribute5Value;
        TOptional<FString> JoinPolicyValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> CustomRolesValue;
        TOptional<FString> GuildMemberDefaultRoleValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateGuildRequest();
        FUpdateGuildRequest(
            const FUpdateGuildRequest& From
        );
        ~FUpdateGuildRequest() = default;

        TSharedPtr<FUpdateGuildRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateGuildRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateGuildRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateGuildRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FUpdateGuildRequest> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FUpdateGuildRequest> WithAttribute1(const TOptional<int32> Attribute1);
        TSharedPtr<FUpdateGuildRequest> WithAttribute2(const TOptional<int32> Attribute2);
        TSharedPtr<FUpdateGuildRequest> WithAttribute3(const TOptional<int32> Attribute3);
        TSharedPtr<FUpdateGuildRequest> WithAttribute4(const TOptional<int32> Attribute4);
        TSharedPtr<FUpdateGuildRequest> WithAttribute5(const TOptional<int32> Attribute5);
        TSharedPtr<FUpdateGuildRequest> WithJoinPolicy(const TOptional<FString> JoinPolicy);
        TSharedPtr<FUpdateGuildRequest> WithCustomRoles(const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> CustomRoles);
        TSharedPtr<FUpdateGuildRequest> WithGuildMemberDefaultRole(const TOptional<FString> GuildMemberDefaultRole);
        TSharedPtr<FUpdateGuildRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetGuildModelName() const;
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
        TOptional<FString> GetJoinPolicy() const;TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> GetCustomRoles() const;
        TOptional<FString> GetGuildMemberDefaultRole() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateGuildRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateGuildRequest, ESPMode::ThreadSafe> FUpdateGuildRequestPtr;
}