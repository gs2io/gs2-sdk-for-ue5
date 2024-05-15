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

namespace Gs2::Guild::Request
{
    class FDeleteMemberByGuildNameRequest;

    class GS2GUILD_API FDeleteMemberByGuildNameRequest final : public TSharedFromThis<FDeleteMemberByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteMemberByGuildNameRequest();
        FDeleteMemberByGuildNameRequest(
            const FDeleteMemberByGuildNameRequest& From
        );
        ~FDeleteMemberByGuildNameRequest() = default;

        TSharedPtr<FDeleteMemberByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteMemberByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteMemberByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDeleteMemberByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FDeleteMemberByGuildNameRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FDeleteMemberByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteMemberByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMemberByGuildNameRequest, ESPMode::ThreadSafe> FDeleteMemberByGuildNameRequestPtr;
}