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
    class FSearchGuildsRequest;

    class GS2GUILD_API FSearchGuildsRequest final : public TSharedFromThis<FSearchGuildsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DisplayNameValue;
        TSharedPtr<TArray<int32>> Attributes1Value;
        TSharedPtr<TArray<int32>> Attributes2Value;
        TSharedPtr<TArray<int32>> Attributes3Value;
        TSharedPtr<TArray<int32>> Attributes4Value;
        TSharedPtr<TArray<int32>> Attributes5Value;
        TSharedPtr<TArray<FString>> JoinPoliciesValue;
        TOptional<bool> IncludeFullMembersGuildValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSearchGuildsRequest();
        FSearchGuildsRequest(
            const FSearchGuildsRequest& From
        );
        ~FSearchGuildsRequest() = default;

        TSharedPtr<FSearchGuildsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSearchGuildsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSearchGuildsRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FSearchGuildsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSearchGuildsRequest> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FSearchGuildsRequest> WithAttributes1(
            const TSharedPtr<TArray<int32>> Attributes1);
        TSharedPtr<FSearchGuildsRequest> WithAttributes2(
            const TSharedPtr<TArray<int32>> Attributes2);
        TSharedPtr<FSearchGuildsRequest> WithAttributes3(
            const TSharedPtr<TArray<int32>> Attributes3);
        TSharedPtr<FSearchGuildsRequest> WithAttributes4(
            const TSharedPtr<TArray<int32>> Attributes4);
        TSharedPtr<FSearchGuildsRequest> WithAttributes5(
            const TSharedPtr<TArray<int32>> Attributes5);
        TSharedPtr<FSearchGuildsRequest> WithJoinPolicies(
            const TSharedPtr<TArray<FString>> JoinPolicies);
        TSharedPtr<FSearchGuildsRequest> WithIncludeFullMembersGuild(const TOptional<bool> IncludeFullMembersGuild);
        TSharedPtr<FSearchGuildsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FSearchGuildsRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FSearchGuildsRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDisplayName() const;
        TSharedPtr<TArray<int32>> GetAttributes1() const;
        TSharedPtr<TArray<int32>> GetAttributes2() const;
        TSharedPtr<TArray<int32>> GetAttributes3() const;
        TSharedPtr<TArray<int32>> GetAttributes4() const;
        TSharedPtr<TArray<int32>> GetAttributes5() const;
        TSharedPtr<TArray<FString>> GetJoinPolicies() const;
        TOptional<bool> GetIncludeFullMembersGuild() const;
        FString GetIncludeFullMembersGuildString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSearchGuildsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSearchGuildsRequest, ESPMode::ThreadSafe> FSearchGuildsRequestPtr;
}