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
    class FGetLastGuildMasterActivityByGuildNameRequest;

    class GS2GUILD_API FGetLastGuildMasterActivityByGuildNameRequest final : public TSharedFromThis<FGetLastGuildMasterActivityByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        
    public:
        
        FGetLastGuildMasterActivityByGuildNameRequest();
        FGetLastGuildMasterActivityByGuildNameRequest(
            const FGetLastGuildMasterActivityByGuildNameRequest& From
        );
        ~FGetLastGuildMasterActivityByGuildNameRequest() = default;

        TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;

        static TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest, ESPMode::ThreadSafe> FGetLastGuildMasterActivityByGuildNameRequestPtr;
}