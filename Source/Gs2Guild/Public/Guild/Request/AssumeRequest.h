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
    class FAssumeRequest;

    class GS2GUILD_API FAssumeRequest final : public TSharedFromThis<FAssumeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAssumeRequest();
        FAssumeRequest(
            const FAssumeRequest& From
        );
        ~FAssumeRequest() = default;

        TSharedPtr<FAssumeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAssumeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAssumeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FAssumeRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FAssumeRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FAssumeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAssumeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAssumeRequest> FAssumeRequestPtr;
}