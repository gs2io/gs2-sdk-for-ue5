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
    class FDeleteGuildByGuildNameRequest;

    class GS2GUILD_API FDeleteGuildByGuildNameRequest final : public TSharedFromThis<FDeleteGuildByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteGuildByGuildNameRequest();
        FDeleteGuildByGuildNameRequest(
            const FDeleteGuildByGuildNameRequest& From
        );
        ~FDeleteGuildByGuildNameRequest() = default;

        TSharedPtr<FDeleteGuildByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteGuildByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteGuildByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDeleteGuildByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FDeleteGuildByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteGuildByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteGuildByGuildNameRequest> FDeleteGuildByGuildNameRequestPtr;
}