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
    class FRejectRequestByGuildNameRequest;

    class GS2GUILD_API FRejectRequestByGuildNameRequest final : public TSharedFromThis<FRejectRequestByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> FromUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRejectRequestByGuildNameRequest();
        FRejectRequestByGuildNameRequest(
            const FRejectRequestByGuildNameRequest& From
        );
        ~FRejectRequestByGuildNameRequest() = default;

        TSharedPtr<FRejectRequestByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRejectRequestByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRejectRequestByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FRejectRequestByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FRejectRequestByGuildNameRequest> WithFromUserId(const TOptional<FString> FromUserId);
        TSharedPtr<FRejectRequestByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetFromUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRejectRequestByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRejectRequestByGuildNameRequest, ESPMode::ThreadSafe> FRejectRequestByGuildNameRequestPtr;
}