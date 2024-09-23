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
    class FSetMaximumCurrentMaximumMemberCountByGuildNameRequest;

    class GS2GUILD_API FSetMaximumCurrentMaximumMemberCountByGuildNameRequest final : public TSharedFromThis<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<int32> ValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetMaximumCurrentMaximumMemberCountByGuildNameRequest();
        FSetMaximumCurrentMaximumMemberCountByGuildNameRequest(
            const FSetMaximumCurrentMaximumMemberCountByGuildNameRequest& From
        );
        ~FSetMaximumCurrentMaximumMemberCountByGuildNameRequest() = default;

        TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest, ESPMode::ThreadSafe> FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr;
}