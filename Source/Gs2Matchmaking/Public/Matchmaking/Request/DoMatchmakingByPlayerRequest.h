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
#include "../Model/Player.h"

namespace Gs2::Matchmaking::Request
{
    class FDoMatchmakingByPlayerRequest;

    class GS2MATCHMAKING_API FDoMatchmakingByPlayerRequest final : public TSharedFromThis<FDoMatchmakingByPlayerRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TSharedPtr<Model::FPlayer> PlayerValue;
        TOptional<FString> MatchmakingContextTokenValue;
        
    public:
        
        FDoMatchmakingByPlayerRequest();
        FDoMatchmakingByPlayerRequest(
            const FDoMatchmakingByPlayerRequest& From
        );
        ~FDoMatchmakingByPlayerRequest() = default;

        TSharedPtr<FDoMatchmakingByPlayerRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoMatchmakingByPlayerRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoMatchmakingByPlayerRequest> WithPlayer(const TSharedPtr<Model::FPlayer> Player);
        TSharedPtr<FDoMatchmakingByPlayerRequest> WithMatchmakingContextToken(const TOptional<FString> MatchmakingContextToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TSharedPtr<Model::FPlayer> GetPlayer() const;
        TOptional<FString> GetMatchmakingContextToken() const;

        static TSharedPtr<FDoMatchmakingByPlayerRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoMatchmakingByPlayerRequest> FDoMatchmakingByPlayerRequestPtr;
}