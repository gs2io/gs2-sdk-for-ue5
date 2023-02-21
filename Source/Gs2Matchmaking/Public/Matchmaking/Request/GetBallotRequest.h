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
    class FGetBallotRequest;

    class GS2MATCHMAKING_API FGetBallotRequest final : public TSharedFromThis<FGetBallotRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RatingNameValue;
        TOptional<FString> GatheringNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> NumberOfPlayerValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetBallotRequest();
        FGetBallotRequest(
            const FGetBallotRequest& From
        );
        ~FGetBallotRequest() = default;

        TSharedPtr<FGetBallotRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBallotRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBallotRequest> WithRatingName(const TOptional<FString> RatingName);
        TSharedPtr<FGetBallotRequest> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FGetBallotRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetBallotRequest> WithNumberOfPlayer(const TOptional<int32> NumberOfPlayer);
        TSharedPtr<FGetBallotRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRatingName() const;
        TOptional<FString> GetGatheringName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetNumberOfPlayer() const;
        FString GetNumberOfPlayerString() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetBallotRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBallotRequest, ESPMode::ThreadSafe> FGetBallotRequestPtr;
}