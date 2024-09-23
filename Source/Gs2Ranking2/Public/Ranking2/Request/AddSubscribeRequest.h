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
    class FAddSubscribeRequest;

    class GS2RANKING2_API FAddSubscribeRequest final : public TSharedFromThis<FAddSubscribeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddSubscribeRequest();
        FAddSubscribeRequest(
            const FAddSubscribeRequest& From
        );
        ~FAddSubscribeRequest() = default;

        TSharedPtr<FAddSubscribeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddSubscribeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddSubscribeRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FAddSubscribeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FAddSubscribeRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FAddSubscribeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddSubscribeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddSubscribeRequest, ESPMode::ThreadSafe> FAddSubscribeRequestPtr;
}