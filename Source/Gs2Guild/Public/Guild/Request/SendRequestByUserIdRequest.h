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
    class FSendRequestByUserIdRequest;

    class GS2GUILD_API FSendRequestByUserIdRequest final : public TSharedFromThis<FSendRequestByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> TargetGuildNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSendRequestByUserIdRequest();
        FSendRequestByUserIdRequest(
            const FSendRequestByUserIdRequest& From
        );
        ~FSendRequestByUserIdRequest() = default;

        TSharedPtr<FSendRequestByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSendRequestByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSendRequestByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendRequestByUserIdRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FSendRequestByUserIdRequest> WithTargetGuildName(const TOptional<FString> TargetGuildName);
        TSharedPtr<FSendRequestByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSendRequestByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetTargetGuildName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSendRequestByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendRequestByUserIdRequest> FSendRequestByUserIdRequestPtr;
}