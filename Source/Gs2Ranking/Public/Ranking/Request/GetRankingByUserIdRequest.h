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

namespace Gs2::Ranking::Request
{
    class FGetRankingByUserIdRequest;

    class GS2RANKING_API FGetRankingByUserIdRequest final : public TSharedFromThis<FGetRankingByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<FString> UniqueIdValue;
        TOptional<FString> AdditionalScopeNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetRankingByUserIdRequest();
        FGetRankingByUserIdRequest(
            const FGetRankingByUserIdRequest& From
        );
        ~FGetRankingByUserIdRequest() = default;

        TSharedPtr<FGetRankingByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRankingByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRankingByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FGetRankingByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetRankingByUserIdRequest> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FGetRankingByUserIdRequest> WithUniqueId(const TOptional<FString> UniqueId);
        TSharedPtr<FGetRankingByUserIdRequest> WithAdditionalScopeName(const TOptional<FString> AdditionalScopeName);
        TSharedPtr<FGetRankingByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<FString> GetUniqueId() const;
        TOptional<FString> GetAdditionalScopeName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetRankingByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequestPtr;
}