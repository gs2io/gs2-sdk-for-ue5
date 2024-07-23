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
    class FGetIgnoreUserByGuildNameRequest;

    class GS2GUILD_API FGetIgnoreUserByGuildNameRequest final : public TSharedFromThis<FGetIgnoreUserByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetIgnoreUserByGuildNameRequest();
        FGetIgnoreUserByGuildNameRequest(
            const FGetIgnoreUserByGuildNameRequest& From
        );
        ~FGetIgnoreUserByGuildNameRequest() = default;

        TSharedPtr<FGetIgnoreUserByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetIgnoreUserByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetIgnoreUserByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FGetIgnoreUserByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FGetIgnoreUserByGuildNameRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetIgnoreUserByGuildNameRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetIgnoreUserByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetIgnoreUserByGuildNameRequest, ESPMode::ThreadSafe> FGetIgnoreUserByGuildNameRequestPtr;
}