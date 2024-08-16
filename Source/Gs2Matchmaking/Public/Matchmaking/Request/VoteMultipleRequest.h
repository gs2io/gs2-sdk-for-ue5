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
#include "../Model/SignedBallot.h"
#include "../Model/GameResult.h"

namespace Gs2::Matchmaking::Request
{
    class FVoteMultipleRequest;

    class GS2MATCHMAKING_API FVoteMultipleRequest final : public TSharedFromThis<FVoteMultipleRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSignedBallot>>> SignedBallotsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResultsValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FVoteMultipleRequest();
        FVoteMultipleRequest(
            const FVoteMultipleRequest& From
        );
        ~FVoteMultipleRequest() = default;

        TSharedPtr<FVoteMultipleRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVoteMultipleRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVoteMultipleRequest> WithSignedBallots(const TSharedPtr<TArray<TSharedPtr<Model::FSignedBallot>>> SignedBallots);
        TSharedPtr<FVoteMultipleRequest> WithGameResults(const TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResults);
        TSharedPtr<FVoteMultipleRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;TSharedPtr<TArray<TSharedPtr<Model::FSignedBallot>>> GetSignedBallots() const;TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GetGameResults() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FVoteMultipleRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVoteMultipleRequest> FVoteMultipleRequestPtr;
}