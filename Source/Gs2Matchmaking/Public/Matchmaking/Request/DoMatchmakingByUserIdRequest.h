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
#include "../Model/Player.h"

namespace Gs2::Matchmaking::Request
{
    class FDoMatchmakingByUserIdRequest;

    class GS2MATCHMAKING_API FDoMatchmakingByUserIdRequest final : public TSharedFromThis<FDoMatchmakingByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FPlayer> PlayerValue;
        TOptional<FString> MatchmakingContextTokenValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDoMatchmakingByUserIdRequest();
        FDoMatchmakingByUserIdRequest(
            const FDoMatchmakingByUserIdRequest& From
        );
        ~FDoMatchmakingByUserIdRequest() = default;

        TSharedPtr<FDoMatchmakingByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoMatchmakingByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoMatchmakingByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDoMatchmakingByUserIdRequest> WithPlayer(const TSharedPtr<Model::FPlayer> Player);
        TSharedPtr<FDoMatchmakingByUserIdRequest> WithMatchmakingContextToken(const TOptional<FString> MatchmakingContextToken);
        TSharedPtr<FDoMatchmakingByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDoMatchmakingByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FPlayer> GetPlayer() const;
        TOptional<FString> GetMatchmakingContextToken() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDoMatchmakingByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoMatchmakingByUserIdRequest, ESPMode::ThreadSafe> FDoMatchmakingByUserIdRequestPtr;
}