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

namespace Gs2::Ranking2::Request
{
    class FDeleteSubscribeRequest;

    class GS2RANKING2_API FDeleteSubscribeRequest final : public TSharedFromThis<FDeleteSubscribeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteSubscribeRequest();
        FDeleteSubscribeRequest(
            const FDeleteSubscribeRequest& From
        );
        ~FDeleteSubscribeRequest() = default;

        TSharedPtr<FDeleteSubscribeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteSubscribeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteSubscribeRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDeleteSubscribeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteSubscribeRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FDeleteSubscribeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteSubscribeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteSubscribeRequest, ESPMode::ThreadSafe> FDeleteSubscribeRequestPtr;
}