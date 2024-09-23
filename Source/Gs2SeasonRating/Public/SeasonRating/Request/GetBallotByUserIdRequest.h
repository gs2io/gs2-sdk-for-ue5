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

namespace Gs2::SeasonRating::Request
{
    class FGetBallotByUserIdRequest;

    class GS2SEASONRATING_API FGetBallotByUserIdRequest final : public TSharedFromThis<FGetBallotByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<FString> SessionNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> NumberOfPlayerValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetBallotByUserIdRequest();
        FGetBallotByUserIdRequest(
            const FGetBallotByUserIdRequest& From
        );
        ~FGetBallotByUserIdRequest() = default;

        TSharedPtr<FGetBallotByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBallotByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBallotByUserIdRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FGetBallotByUserIdRequest> WithSessionName(const TOptional<FString> SessionName);
        TSharedPtr<FGetBallotByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetBallotByUserIdRequest> WithNumberOfPlayer(const TOptional<int32> NumberOfPlayer);
        TSharedPtr<FGetBallotByUserIdRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FGetBallotByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<FString> GetSessionName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetNumberOfPlayer() const;
        FString GetNumberOfPlayerString() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetBallotByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBallotByUserIdRequest, ESPMode::ThreadSafe> FGetBallotByUserIdRequestPtr;
}