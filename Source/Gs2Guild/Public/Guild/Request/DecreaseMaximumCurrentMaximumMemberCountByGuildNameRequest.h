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
    class FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest;

    class GS2GUILD_API FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest final : public TSharedFromThis<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<int32> ValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest();
        FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest(
            const FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest& From
        );
        ~FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest() = default;

        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest> FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr;
}