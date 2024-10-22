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

namespace Gs2::Matchmaking::Request
{
    class FGetJoinedSeasonGatheringByUserIdRequest;

    class GS2MATCHMAKING_API FGetJoinedSeasonGatheringByUserIdRequest final : public TSharedFromThis<FGetJoinedSeasonGatheringByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetJoinedSeasonGatheringByUserIdRequest();
        FGetJoinedSeasonGatheringByUserIdRequest(
            const FGetJoinedSeasonGatheringByUserIdRequest& From
        );
        ~FGetJoinedSeasonGatheringByUserIdRequest() = default;

        TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetJoinedSeasonGatheringByUserIdRequest> FGetJoinedSeasonGatheringByUserIdRequestPtr;
}