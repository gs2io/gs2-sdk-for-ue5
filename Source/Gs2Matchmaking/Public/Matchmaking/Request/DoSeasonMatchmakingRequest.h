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
    class FDoSeasonMatchmakingRequest;

    class GS2MATCHMAKING_API FDoSeasonMatchmakingRequest final : public TSharedFromThis<FDoSeasonMatchmakingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MatchmakingContextTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDoSeasonMatchmakingRequest();
        FDoSeasonMatchmakingRequest(
            const FDoSeasonMatchmakingRequest& From
        );
        ~FDoSeasonMatchmakingRequest() = default;

        TSharedPtr<FDoSeasonMatchmakingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoSeasonMatchmakingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoSeasonMatchmakingRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FDoSeasonMatchmakingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDoSeasonMatchmakingRequest> WithMatchmakingContextToken(const TOptional<FString> MatchmakingContextToken);
        TSharedPtr<FDoSeasonMatchmakingRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMatchmakingContextToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDoSeasonMatchmakingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoSeasonMatchmakingRequest> FDoSeasonMatchmakingRequestPtr;
}