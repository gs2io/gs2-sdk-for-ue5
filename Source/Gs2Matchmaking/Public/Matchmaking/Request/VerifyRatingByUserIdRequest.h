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
    class FVerifyRatingByUserIdRequest;

    class GS2MATCHMAKING_API FVerifyRatingByUserIdRequest final : public TSharedFromThis<FVerifyRatingByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RatingNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<float> RateValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRatingByUserIdRequest();
        FVerifyRatingByUserIdRequest(
            const FVerifyRatingByUserIdRequest& From
        );
        ~FVerifyRatingByUserIdRequest() = default;

        TSharedPtr<FVerifyRatingByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRatingByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRatingByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyRatingByUserIdRequest> WithRatingName(const TOptional<FString> RatingName);
        TSharedPtr<FVerifyRatingByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRatingByUserIdRequest> WithRateValue(const TOptional<float> RateValue);
        TSharedPtr<FVerifyRatingByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyRatingByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRatingName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<float> GetRateValue() const;
        FString GetRateValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRatingByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRatingByUserIdRequest> FVerifyRatingByUserIdRequestPtr;
}