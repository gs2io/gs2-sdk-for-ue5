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
    class FGetGuildByUserIdRequest;

    class GS2GUILD_API FGetGuildByUserIdRequest final : public TSharedFromThis<FGetGuildByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetGuildByUserIdRequest();
        FGetGuildByUserIdRequest(
            const FGetGuildByUserIdRequest& From
        );
        ~FGetGuildByUserIdRequest() = default;

        TSharedPtr<FGetGuildByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetGuildByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetGuildByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetGuildByUserIdRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FGetGuildByUserIdRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FGetGuildByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetGuildByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGuildByUserIdRequest, ESPMode::ThreadSafe> FGetGuildByUserIdRequestPtr;
}