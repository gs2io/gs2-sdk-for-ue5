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
    class FUpdateMemberMetadataRequest;

    class GS2GUILD_API FUpdateMemberMetadataRequest final : public TSharedFromThis<FUpdateMemberMetadataRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateMemberMetadataRequest();
        FUpdateMemberMetadataRequest(
            const FUpdateMemberMetadataRequest& From
        );
        ~FUpdateMemberMetadataRequest() = default;

        TSharedPtr<FUpdateMemberMetadataRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMemberMetadataRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMemberMetadataRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FUpdateMemberMetadataRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FUpdateMemberMetadataRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateMemberMetadataRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateMemberMetadataRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateMemberMetadataRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMemberMetadataRequest> FUpdateMemberMetadataRequestPtr;
}