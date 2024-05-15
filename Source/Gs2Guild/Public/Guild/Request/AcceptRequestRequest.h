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
    class FAcceptRequestRequest;

    class GS2GUILD_API FAcceptRequestRequest final : public TSharedFromThis<FAcceptRequestRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> FromUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcceptRequestRequest();
        FAcceptRequestRequest(
            const FAcceptRequestRequest& From
        );
        ~FAcceptRequestRequest() = default;

        TSharedPtr<FAcceptRequestRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcceptRequestRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcceptRequestRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FAcceptRequestRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FAcceptRequestRequest> WithFromUserId(const TOptional<FString> FromUserId);
        TSharedPtr<FAcceptRequestRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetFromUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcceptRequestRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcceptRequestRequest, ESPMode::ThreadSafe> FAcceptRequestRequestPtr;
}