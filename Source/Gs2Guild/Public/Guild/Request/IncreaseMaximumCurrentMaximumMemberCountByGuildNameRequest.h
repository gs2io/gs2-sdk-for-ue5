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
    class FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest;

    class GS2GUILD_API FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest final : public TSharedFromThis<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<int32> ValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest();
        FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest(
            const FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest& From
        );
        ~FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest() = default;

        TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr;
}