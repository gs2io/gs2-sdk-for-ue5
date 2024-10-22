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
    class FSearchGuildsByUserIdRequest;

    class GS2GUILD_API FSearchGuildsByUserIdRequest final : public TSharedFromThis<FSearchGuildsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DisplayNameValue;
        TSharedPtr<TArray<int32>> Attributes1Value;
        TSharedPtr<TArray<int32>> Attributes2Value;
        TSharedPtr<TArray<int32>> Attributes3Value;
        TSharedPtr<TArray<int32>> Attributes4Value;
        TSharedPtr<TArray<int32>> Attributes5Value;
        TSharedPtr<TArray<FString>> JoinPoliciesValue;
        TOptional<bool> IncludeFullMembersGuildValue;
        TOptional<FString> OrderByValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSearchGuildsByUserIdRequest();
        FSearchGuildsByUserIdRequest(
            const FSearchGuildsByUserIdRequest& From
        );
        ~FSearchGuildsByUserIdRequest() = default;

        TSharedPtr<FSearchGuildsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithAttributes1(
            const TSharedPtr<TArray<int32>> Attributes1);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithAttributes2(
            const TSharedPtr<TArray<int32>> Attributes2);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithAttributes3(
            const TSharedPtr<TArray<int32>> Attributes3);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithAttributes4(
            const TSharedPtr<TArray<int32>> Attributes4);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithAttributes5(
            const TSharedPtr<TArray<int32>> Attributes5);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithJoinPolicies(
            const TSharedPtr<TArray<FString>> JoinPolicies);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithIncludeFullMembersGuild(const TOptional<bool> IncludeFullMembersGuild);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithOrderBy(const TOptional<FString> OrderBy);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSearchGuildsByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDisplayName() const;
        TSharedPtr<TArray<int32>> GetAttributes1() const;
        TSharedPtr<TArray<int32>> GetAttributes2() const;
        TSharedPtr<TArray<int32>> GetAttributes3() const;
        TSharedPtr<TArray<int32>> GetAttributes4() const;
        TSharedPtr<TArray<int32>> GetAttributes5() const;
        TSharedPtr<TArray<FString>> GetJoinPolicies() const;
        TOptional<bool> GetIncludeFullMembersGuild() const;
        FString GetIncludeFullMembersGuildString() const;
        TOptional<FString> GetOrderBy() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSearchGuildsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequestPtr;
}