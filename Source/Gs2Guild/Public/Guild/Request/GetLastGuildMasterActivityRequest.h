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
    class FGetLastGuildMasterActivityRequest;

    class GS2GUILD_API FGetLastGuildMasterActivityRequest final : public TSharedFromThis<FGetLastGuildMasterActivityRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetLastGuildMasterActivityRequest();
        FGetLastGuildMasterActivityRequest(
            const FGetLastGuildMasterActivityRequest& From
        );
        ~FGetLastGuildMasterActivityRequest() = default;

        TSharedPtr<FGetLastGuildMasterActivityRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetLastGuildMasterActivityRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetLastGuildMasterActivityRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FGetLastGuildMasterActivityRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetLastGuildMasterActivityRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetLastGuildMasterActivityRequest, ESPMode::ThreadSafe> FGetLastGuildMasterActivityRequestPtr;
}