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
    class FBatchUpdateMemberRoleByGuildNameRequest;

    class GS2GUILD_API FBatchUpdateMemberRoleByGuildNameRequest final : public TSharedFromThis<FBatchUpdateMemberRoleByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMember>>> MembersValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBatchUpdateMemberRoleByGuildNameRequest();
        FBatchUpdateMemberRoleByGuildNameRequest(
            const FBatchUpdateMemberRoleByGuildNameRequest& From
        );
        ~FBatchUpdateMemberRoleByGuildNameRequest() = default;

        TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> WithMembers(const TSharedPtr<TArray<TSharedPtr<Model::FMember>>> Members);
        TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;TSharedPtr<TArray<TSharedPtr<Model::FMember>>> GetMembers() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchUpdateMemberRoleByGuildNameRequest> FBatchUpdateMemberRoleByGuildNameRequestPtr;
}