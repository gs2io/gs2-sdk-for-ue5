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
    class FGetJoinedSeasonGatheringRequest;

    class GS2MATCHMAKING_API FGetJoinedSeasonGatheringRequest final : public TSharedFromThis<FGetJoinedSeasonGatheringRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        
    public:
        
        FGetJoinedSeasonGatheringRequest();
        FGetJoinedSeasonGatheringRequest(
            const FGetJoinedSeasonGatheringRequest& From
        );
        ~FGetJoinedSeasonGatheringRequest() = default;

        TSharedPtr<FGetJoinedSeasonGatheringRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetJoinedSeasonGatheringRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetJoinedSeasonGatheringRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetJoinedSeasonGatheringRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FGetJoinedSeasonGatheringRequest> WithSeason(const TOptional<int64> Season);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        static TSharedPtr<FGetJoinedSeasonGatheringRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetJoinedSeasonGatheringRequest> FGetJoinedSeasonGatheringRequestPtr;
}