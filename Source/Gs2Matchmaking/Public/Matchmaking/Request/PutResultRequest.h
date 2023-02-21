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
#include "../Model/GameResult.h"

namespace Gs2::Matchmaking::Request
{
    class FPutResultRequest;

    class GS2MATCHMAKING_API FPutResultRequest final : public TSharedFromThis<FPutResultRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RatingNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResultsValue;
        
    public:
        
        FPutResultRequest();
        FPutResultRequest(
            const FPutResultRequest& From
        );
        ~FPutResultRequest() = default;

        TSharedPtr<FPutResultRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPutResultRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPutResultRequest> WithRatingName(const TOptional<FString> RatingName);
        TSharedPtr<FPutResultRequest> WithGameResults(const TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResults);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRatingName() const;TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GetGameResults() const;

        static TSharedPtr<FPutResultRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPutResultRequest, ESPMode::ThreadSafe> FPutResultRequestPtr;
}