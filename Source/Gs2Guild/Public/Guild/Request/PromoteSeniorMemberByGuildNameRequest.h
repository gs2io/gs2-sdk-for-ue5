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
    class FPromoteSeniorMemberByGuildNameRequest;

    class GS2GUILD_API FPromoteSeniorMemberByGuildNameRequest final : public TSharedFromThis<FPromoteSeniorMemberByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPromoteSeniorMemberByGuildNameRequest();
        FPromoteSeniorMemberByGuildNameRequest(
            const FPromoteSeniorMemberByGuildNameRequest& From
        );
        ~FPromoteSeniorMemberByGuildNameRequest() = default;

        TSharedPtr<FPromoteSeniorMemberByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPromoteSeniorMemberByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPromoteSeniorMemberByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FPromoteSeniorMemberByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FPromoteSeniorMemberByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPromoteSeniorMemberByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPromoteSeniorMemberByGuildNameRequest> FPromoteSeniorMemberByGuildNameRequestPtr;
}