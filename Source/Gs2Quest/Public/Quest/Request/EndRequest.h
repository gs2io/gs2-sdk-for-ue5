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
#include "../Model/Reward.h"
#include "../Model/Config.h"

namespace Gs2::Quest::Request
{
    class FEndRequest;

    class GS2QUEST_API FEndRequest final : public TSharedFromThis<FEndRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FReward>>> RewardsValue;
        TOptional<bool> IsCompleteValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FEndRequest();
        FEndRequest(
            const FEndRequest& From
        );
        ~FEndRequest() = default;

        TSharedPtr<FEndRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FEndRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FEndRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FEndRequest> WithRewards(const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards);
        TSharedPtr<FEndRequest> WithIsComplete(const TOptional<bool> IsComplete);
        TSharedPtr<FEndRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FEndRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FReward>>> GetRewards() const;
        TOptional<bool> GetIsComplete() const;
        FString GetIsCompleteString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FEndRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEndRequest, ESPMode::ThreadSafe> FEndRequestPtr;
}