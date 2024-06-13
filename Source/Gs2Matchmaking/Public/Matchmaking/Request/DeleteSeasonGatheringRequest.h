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
    class FDeleteSeasonGatheringRequest;

    class GS2MATCHMAKING_API FDeleteSeasonGatheringRequest final : public TSharedFromThis<FDeleteSeasonGatheringRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> TierValue;
        TOptional<FString> SeasonGatheringNameValue;
        
    public:
        
        FDeleteSeasonGatheringRequest();
        FDeleteSeasonGatheringRequest(
            const FDeleteSeasonGatheringRequest& From
        );
        ~FDeleteSeasonGatheringRequest() = default;

        TSharedPtr<FDeleteSeasonGatheringRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteSeasonGatheringRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteSeasonGatheringRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FDeleteSeasonGatheringRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FDeleteSeasonGatheringRequest> WithTier(const TOptional<int64> Tier);
        TSharedPtr<FDeleteSeasonGatheringRequest> WithSeasonGatheringName(const TOptional<FString> SeasonGatheringName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetTier() const;
        FString GetTierString() const;
        TOptional<FString> GetSeasonGatheringName() const;

        static TSharedPtr<FDeleteSeasonGatheringRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteSeasonGatheringRequest, ESPMode::ThreadSafe> FDeleteSeasonGatheringRequestPtr;
}