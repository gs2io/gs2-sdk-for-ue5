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

namespace Gs2::Lottery::Request
{
    class FDescribeProbabilitiesRequest;

    class GS2LOTTERY_API FDescribeProbabilitiesRequest final : public TSharedFromThis<FDescribeProbabilitiesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LotteryNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FDescribeProbabilitiesRequest();
        FDescribeProbabilitiesRequest(
            const FDescribeProbabilitiesRequest& From
        );
        ~FDescribeProbabilitiesRequest() = default;

        TSharedPtr<FDescribeProbabilitiesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeProbabilitiesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeProbabilitiesRequest> WithLotteryName(const TOptional<FString> LotteryName);
        TSharedPtr<FDescribeProbabilitiesRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLotteryName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FDescribeProbabilitiesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeProbabilitiesRequest, ESPMode::ThreadSafe> FDescribeProbabilitiesRequestPtr;
}