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

namespace Gs2::Ranking2::Request
{
    class FGetGlobalRankingByUserIdRequest;

    class GS2RANKING2_API FGetGlobalRankingByUserIdRequest final : public TSharedFromThis<FGetGlobalRankingByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetGlobalRankingByUserIdRequest();
        FGetGlobalRankingByUserIdRequest(
            const FGetGlobalRankingByUserIdRequest& From
        );
        ~FGetGlobalRankingByUserIdRequest() = default;

        TSharedPtr<FGetGlobalRankingByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetGlobalRankingByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetGlobalRankingByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGetGlobalRankingByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetGlobalRankingByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FGetGlobalRankingByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetGlobalRankingByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGlobalRankingByUserIdRequest> FGetGlobalRankingByUserIdRequestPtr;
}