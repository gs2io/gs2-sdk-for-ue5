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
    class FVerifyIncludeParticipantRequest;

    class GS2MATCHMAKING_API FVerifyIncludeParticipantRequest final : public TSharedFromThis<FVerifyIncludeParticipantRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> TierValue;
        TOptional<FString> SeasonGatheringNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyIncludeParticipantRequest();
        FVerifyIncludeParticipantRequest(
            const FVerifyIncludeParticipantRequest& From
        );
        ~FVerifyIncludeParticipantRequest() = default;

        TSharedPtr<FVerifyIncludeParticipantRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithTier(const TOptional<int64> Tier);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithSeasonGatheringName(const TOptional<FString> SeasonGatheringName);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyIncludeParticipantRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetTier() const;
        FString GetTierString() const;
        TOptional<FString> GetSeasonGatheringName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyIncludeParticipantRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyIncludeParticipantRequest, ESPMode::ThreadSafe> FVerifyIncludeParticipantRequestPtr;
}