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
#include "../Model/Member.h"

namespace Gs2::Guild::Request
{
    class FBatchUpdateMemberRoleRequest;

    class GS2GUILD_API FBatchUpdateMemberRoleRequest final : public TSharedFromThis<FBatchUpdateMemberRoleRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMember>>> MembersValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBatchUpdateMemberRoleRequest();
        FBatchUpdateMemberRoleRequest(
            const FBatchUpdateMemberRoleRequest& From
        );
        ~FBatchUpdateMemberRoleRequest() = default;

        TSharedPtr<FBatchUpdateMemberRoleRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBatchUpdateMemberRoleRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBatchUpdateMemberRoleRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FBatchUpdateMemberRoleRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FBatchUpdateMemberRoleRequest> WithMembers(const TSharedPtr<TArray<TSharedPtr<Model::FMember>>> Members);
        TSharedPtr<FBatchUpdateMemberRoleRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FMember>>> GetMembers() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBatchUpdateMemberRoleRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchUpdateMemberRoleRequest> FBatchUpdateMemberRoleRequestPtr;
}