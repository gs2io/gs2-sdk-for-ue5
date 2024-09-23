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
    class FAddIgnoreUserByGuildNameRequest;

    class GS2GUILD_API FAddIgnoreUserByGuildNameRequest final : public TSharedFromThis<FAddIgnoreUserByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddIgnoreUserByGuildNameRequest();
        FAddIgnoreUserByGuildNameRequest(
            const FAddIgnoreUserByGuildNameRequest& From
        );
        ~FAddIgnoreUserByGuildNameRequest() = default;

        TSharedPtr<FAddIgnoreUserByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddIgnoreUserByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddIgnoreUserByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FAddIgnoreUserByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FAddIgnoreUserByGuildNameRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddIgnoreUserByGuildNameRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAddIgnoreUserByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddIgnoreUserByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddIgnoreUserByGuildNameRequest, ESPMode::ThreadSafe> FAddIgnoreUserByGuildNameRequestPtr;
}