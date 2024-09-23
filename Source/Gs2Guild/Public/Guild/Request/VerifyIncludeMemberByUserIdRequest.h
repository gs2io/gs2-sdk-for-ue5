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
    class FVerifyIncludeMemberByUserIdRequest;

    class GS2GUILD_API FVerifyIncludeMemberByUserIdRequest final : public TSharedFromThis<FVerifyIncludeMemberByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyIncludeMemberByUserIdRequest();
        FVerifyIncludeMemberByUserIdRequest(
            const FVerifyIncludeMemberByUserIdRequest& From
        );
        ~FVerifyIncludeMemberByUserIdRequest() = default;

        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyIncludeMemberByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyIncludeMemberByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyIncludeMemberByUserIdRequest, ESPMode::ThreadSafe> FVerifyIncludeMemberByUserIdRequestPtr;
}