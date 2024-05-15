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
    class FGetReceiveRequestByGuildNameRequest;

    class GS2GUILD_API FGetReceiveRequestByGuildNameRequest final : public TSharedFromThis<FGetReceiveRequestByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> FromUserIdValue;
        
    public:
        
        FGetReceiveRequestByGuildNameRequest();
        FGetReceiveRequestByGuildNameRequest(
            const FGetReceiveRequestByGuildNameRequest& From
        );
        ~FGetReceiveRequestByGuildNameRequest() = default;

        TSharedPtr<FGetReceiveRequestByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetReceiveRequestByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetReceiveRequestByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FGetReceiveRequestByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FGetReceiveRequestByGuildNameRequest> WithFromUserId(const TOptional<FString> FromUserId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetFromUserId() const;

        static TSharedPtr<FGetReceiveRequestByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetReceiveRequestByGuildNameRequest, ESPMode::ThreadSafe> FGetReceiveRequestByGuildNameRequestPtr;
}