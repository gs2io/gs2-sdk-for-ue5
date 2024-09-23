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
    class FDescribePrizeLimitsRequest;

    class GS2LOTTERY_API FDescribePrizeLimitsRequest final : public TSharedFromThis<FDescribePrizeLimitsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribePrizeLimitsRequest();
        FDescribePrizeLimitsRequest(
            const FDescribePrizeLimitsRequest& From
        );
        ~FDescribePrizeLimitsRequest() = default;

        TSharedPtr<FDescribePrizeLimitsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribePrizeLimitsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribePrizeLimitsRequest> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FDescribePrizeLimitsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribePrizeLimitsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribePrizeLimitsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribePrizeLimitsRequest, ESPMode::ThreadSafe> FDescribePrizeLimitsRequestPtr;
}