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

namespace Gs2::SeasonRating::Request
{
    class FVoteRequest;

    class GS2SEASONRATING_API FVoteRequest final : public TSharedFromThis<FVoteRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BallotBodyValue;
        TOptional<FString> BallotSignatureValue;
        TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResultsValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FVoteRequest();
        FVoteRequest(
            const FVoteRequest& From
        );
        ~FVoteRequest() = default;

        TSharedPtr<FVoteRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVoteRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVoteRequest> WithBallotBody(const TOptional<FString> BallotBody);
        TSharedPtr<FVoteRequest> WithBallotSignature(const TOptional<FString> BallotSignature);
        TSharedPtr<FVoteRequest> WithGameResults(const TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResults);
        TSharedPtr<FVoteRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBallotBody() const;
        TOptional<FString> GetBallotSignature() const;TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GetGameResults() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FVoteRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVoteRequest, ESPMode::ThreadSafe> FVoteRequestPtr;
}