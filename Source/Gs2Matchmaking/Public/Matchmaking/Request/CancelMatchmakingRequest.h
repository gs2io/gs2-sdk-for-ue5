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
    class FCancelMatchmakingRequest;

    class GS2MATCHMAKING_API FCancelMatchmakingRequest final : public TSharedFromThis<FCancelMatchmakingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GatheringNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCancelMatchmakingRequest();
        FCancelMatchmakingRequest(
            const FCancelMatchmakingRequest& From
        );
        ~FCancelMatchmakingRequest() = default;

        TSharedPtr<FCancelMatchmakingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCancelMatchmakingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCancelMatchmakingRequest> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FCancelMatchmakingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FCancelMatchmakingRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGatheringName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCancelMatchmakingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCancelMatchmakingRequest, ESPMode::ThreadSafe> FCancelMatchmakingRequestPtr;
}