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
    class FCommitVoteRequest;

    class GS2SEASONRATING_API FCommitVoteRequest final : public TSharedFromThis<FCommitVoteRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<FString> SessionNameValue;
        
    public:
        
        FCommitVoteRequest();
        FCommitVoteRequest(
            const FCommitVoteRequest& From
        );
        ~FCommitVoteRequest() = default;

        TSharedPtr<FCommitVoteRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCommitVoteRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCommitVoteRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FCommitVoteRequest> WithSessionName(const TOptional<FString> SessionName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<FString> GetSessionName() const;

        static TSharedPtr<FCommitVoteRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCommitVoteRequest, ESPMode::ThreadSafe> FCommitVoteRequestPtr;
}