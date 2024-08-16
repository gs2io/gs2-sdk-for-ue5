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
    class FAssumeByUserIdRequest;

    class GS2GUILD_API FAssumeByUserIdRequest final : public TSharedFromThis<FAssumeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAssumeByUserIdRequest();
        FAssumeByUserIdRequest(
            const FAssumeByUserIdRequest& From
        );
        ~FAssumeByUserIdRequest() = default;

        TSharedPtr<FAssumeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAssumeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAssumeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAssumeByUserIdRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FAssumeByUserIdRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FAssumeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAssumeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAssumeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAssumeByUserIdRequest> FAssumeByUserIdRequestPtr;
}