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
    class FPromoteSeniorMemberRequest;

    class GS2GUILD_API FPromoteSeniorMemberRequest final : public TSharedFromThis<FPromoteSeniorMemberRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPromoteSeniorMemberRequest();
        FPromoteSeniorMemberRequest(
            const FPromoteSeniorMemberRequest& From
        );
        ~FPromoteSeniorMemberRequest() = default;

        TSharedPtr<FPromoteSeniorMemberRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPromoteSeniorMemberRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPromoteSeniorMemberRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FPromoteSeniorMemberRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPromoteSeniorMemberRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPromoteSeniorMemberRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPromoteSeniorMemberRequest> FPromoteSeniorMemberRequestPtr;
}