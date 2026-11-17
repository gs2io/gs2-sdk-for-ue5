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
    class FVerifyRatingRequest;

    class GS2MATCHMAKING_API FVerifyRatingRequest final : public TSharedFromThis<FVerifyRatingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RatingNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<float> RateValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRatingRequest();
        FVerifyRatingRequest(
            const FVerifyRatingRequest& From
        );
        ~FVerifyRatingRequest() = default;

        TSharedPtr<FVerifyRatingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRatingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRatingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyRatingRequest> WithRatingName(const TOptional<FString> RatingName);
        TSharedPtr<FVerifyRatingRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRatingRequest> WithRateValue(const TOptional<float> RateValue);
        TSharedPtr<FVerifyRatingRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRatingName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<float> GetRateValue() const;
        FString GetRateValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRatingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRatingRequest> FVerifyRatingRequestPtr;
}