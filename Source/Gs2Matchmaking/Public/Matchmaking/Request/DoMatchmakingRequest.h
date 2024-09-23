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
    class FDoMatchmakingRequest;

    class GS2MATCHMAKING_API FDoMatchmakingRequest final : public TSharedFromThis<FDoMatchmakingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<Model::FPlayer> PlayerValue;
        TOptional<FString> MatchmakingContextTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDoMatchmakingRequest();
        FDoMatchmakingRequest(
            const FDoMatchmakingRequest& From
        );
        ~FDoMatchmakingRequest() = default;

        TSharedPtr<FDoMatchmakingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoMatchmakingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoMatchmakingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDoMatchmakingRequest> WithPlayer(const TSharedPtr<Model::FPlayer> Player);
        TSharedPtr<FDoMatchmakingRequest> WithMatchmakingContextToken(const TOptional<FString> MatchmakingContextToken);
        TSharedPtr<FDoMatchmakingRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<Model::FPlayer> GetPlayer() const;
        TOptional<FString> GetMatchmakingContextToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDoMatchmakingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoMatchmakingRequest, ESPMode::ThreadSafe> FDoMatchmakingRequestPtr;
}