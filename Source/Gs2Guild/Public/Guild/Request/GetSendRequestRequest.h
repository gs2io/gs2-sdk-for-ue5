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
    class FGetSendRequestRequest;

    class GS2GUILD_API FGetSendRequestRequest final : public TSharedFromThis<FGetSendRequestRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> TargetGuildNameValue;
        
    public:
        
        FGetSendRequestRequest();
        FGetSendRequestRequest(
            const FGetSendRequestRequest& From
        );
        ~FGetSendRequestRequest() = default;

        TSharedPtr<FGetSendRequestRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSendRequestRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSendRequestRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetSendRequestRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FGetSendRequestRequest> WithTargetGuildName(const TOptional<FString> TargetGuildName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetTargetGuildName() const;

        static TSharedPtr<FGetSendRequestRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSendRequestRequest, ESPMode::ThreadSafe> FGetSendRequestRequestPtr;
}