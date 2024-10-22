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
    class FVerifyIncludeParticipantByUserIdRequest;

    class GS2MATCHMAKING_API FVerifyIncludeParticipantByUserIdRequest final : public TSharedFromThis<FVerifyIncludeParticipantByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> TierValue;
        TOptional<FString> SeasonGatheringNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyIncludeParticipantByUserIdRequest();
        FVerifyIncludeParticipantByUserIdRequest(
            const FVerifyIncludeParticipantByUserIdRequest& From
        );
        ~FVerifyIncludeParticipantByUserIdRequest() = default;

        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithTier(const TOptional<int64> Tier);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithSeasonGatheringName(const TOptional<FString> SeasonGatheringName);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetTier() const;
        FString GetTierString() const;
        TOptional<FString> GetSeasonGatheringName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyIncludeParticipantByUserIdRequest> FVerifyIncludeParticipantByUserIdRequestPtr;
}