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
    class FUpdateMemberMetadataByUserIdRequest;

    class GS2GUILD_API FUpdateMemberMetadataByUserIdRequest final : public TSharedFromThis<FUpdateMemberMetadataByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateMemberMetadataByUserIdRequest();
        FUpdateMemberMetadataByUserIdRequest(
            const FUpdateMemberMetadataByUserIdRequest& From
        );
        ~FUpdateMemberMetadataByUserIdRequest() = default;

        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateMemberMetadataByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateMemberMetadataByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMemberMetadataByUserIdRequest> FUpdateMemberMetadataByUserIdRequestPtr;
}