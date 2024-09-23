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
    class FVerifyIncludeMemberRequest;

    class GS2GUILD_API FVerifyIncludeMemberRequest final : public TSharedFromThis<FVerifyIncludeMemberRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyIncludeMemberRequest();
        FVerifyIncludeMemberRequest(
            const FVerifyIncludeMemberRequest& From
        );
        ~FVerifyIncludeMemberRequest() = default;

        TSharedPtr<FVerifyIncludeMemberRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyIncludeMemberRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyIncludeMemberRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FVerifyIncludeMemberRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FVerifyIncludeMemberRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyIncludeMemberRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyIncludeMemberRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyIncludeMemberRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyIncludeMemberRequest, ESPMode::ThreadSafe> FVerifyIncludeMemberRequestPtr;
}