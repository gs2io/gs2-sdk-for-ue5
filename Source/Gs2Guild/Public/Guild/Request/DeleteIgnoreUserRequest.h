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
    class FDeleteIgnoreUserRequest;

    class GS2GUILD_API FDeleteIgnoreUserRequest final : public TSharedFromThis<FDeleteIgnoreUserRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteIgnoreUserRequest();
        FDeleteIgnoreUserRequest(
            const FDeleteIgnoreUserRequest& From
        );
        ~FDeleteIgnoreUserRequest() = default;

        TSharedPtr<FDeleteIgnoreUserRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteIgnoreUserRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteIgnoreUserRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDeleteIgnoreUserRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteIgnoreUserRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteIgnoreUserRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteIgnoreUserRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteIgnoreUserRequest, ESPMode::ThreadSafe> FDeleteIgnoreUserRequestPtr;
}