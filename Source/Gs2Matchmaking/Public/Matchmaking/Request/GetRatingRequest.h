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
    class FGetRatingRequest;

    class GS2MATCHMAKING_API FGetRatingRequest final : public TSharedFromThis<FGetRatingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RatingNameValue;
        
    public:
        
        FGetRatingRequest();
        FGetRatingRequest(
            const FGetRatingRequest& From
        );
        ~FGetRatingRequest() = default;

        TSharedPtr<FGetRatingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRatingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRatingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetRatingRequest> WithRatingName(const TOptional<FString> RatingName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRatingName() const;

        static TSharedPtr<FGetRatingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRatingRequest, ESPMode::ThreadSafe> FGetRatingRequestPtr;
}