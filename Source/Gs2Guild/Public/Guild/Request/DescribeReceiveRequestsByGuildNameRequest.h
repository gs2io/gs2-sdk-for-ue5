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
    class FDescribeReceiveRequestsByGuildNameRequest;

    class GS2GUILD_API FDescribeReceiveRequestsByGuildNameRequest final : public TSharedFromThis<FDescribeReceiveRequestsByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeReceiveRequestsByGuildNameRequest();
        FDescribeReceiveRequestsByGuildNameRequest(
            const FDescribeReceiveRequestsByGuildNameRequest& From
        );
        ~FDescribeReceiveRequestsByGuildNameRequest() = default;

        TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeReceiveRequestsByGuildNameRequest, ESPMode::ThreadSafe> FDescribeReceiveRequestsByGuildNameRequestPtr;
}