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
    class FDeleteRequestRequest;

    class GS2GUILD_API FDeleteRequestRequest final : public TSharedFromThis<FDeleteRequestRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> TargetGuildNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteRequestRequest();
        FDeleteRequestRequest(
            const FDeleteRequestRequest& From
        );
        ~FDeleteRequestRequest() = default;

        TSharedPtr<FDeleteRequestRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteRequestRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteRequestRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteRequestRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDeleteRequestRequest> WithTargetGuildName(const TOptional<FString> TargetGuildName);
        TSharedPtr<FDeleteRequestRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetTargetGuildName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteRequestRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteRequestRequest> FDeleteRequestRequestPtr;
}