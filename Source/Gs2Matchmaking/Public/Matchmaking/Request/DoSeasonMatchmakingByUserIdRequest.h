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

namespace Gs2::Matchmaking::Request
{
    class FDoSeasonMatchmakingByUserIdRequest;

    class GS2MATCHMAKING_API FDoSeasonMatchmakingByUserIdRequest final : public TSharedFromThis<FDoSeasonMatchmakingByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MatchmakingContextTokenValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDoSeasonMatchmakingByUserIdRequest();
        FDoSeasonMatchmakingByUserIdRequest(
            const FDoSeasonMatchmakingByUserIdRequest& From
        );
        ~FDoSeasonMatchmakingByUserIdRequest() = default;

        TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> WithMatchmakingContextToken(const TOptional<FString> MatchmakingContextToken);
        TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMatchmakingContextToken() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDoSeasonMatchmakingByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoSeasonMatchmakingByUserIdRequest, ESPMode::ThreadSafe> FDoSeasonMatchmakingByUserIdRequestPtr;
}