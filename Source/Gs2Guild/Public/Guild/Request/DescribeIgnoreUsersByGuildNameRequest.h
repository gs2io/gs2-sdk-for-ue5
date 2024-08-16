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
    class FDescribeIgnoreUsersByGuildNameRequest;

    class GS2GUILD_API FDescribeIgnoreUsersByGuildNameRequest final : public TSharedFromThis<FDescribeIgnoreUsersByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeIgnoreUsersByGuildNameRequest();
        FDescribeIgnoreUsersByGuildNameRequest(
            const FDescribeIgnoreUsersByGuildNameRequest& From
        );
        ~FDescribeIgnoreUsersByGuildNameRequest() = default;

        TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeIgnoreUsersByGuildNameRequest> FDescribeIgnoreUsersByGuildNameRequestPtr;
}