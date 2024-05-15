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
    class FGetGuildModelRequest;

    class GS2GUILD_API FGetGuildModelRequest final : public TSharedFromThis<FGetGuildModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        
    public:
        
        FGetGuildModelRequest();
        FGetGuildModelRequest(
            const FGetGuildModelRequest& From
        );
        ~FGetGuildModelRequest() = default;

        TSharedPtr<FGetGuildModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetGuildModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetGuildModelRequest> WithGuildModelName(const TOptional<FString> GuildModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;

        static TSharedPtr<FGetGuildModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGuildModelRequest, ESPMode::ThreadSafe> FGetGuildModelRequestPtr;
}