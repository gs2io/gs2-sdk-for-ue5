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

namespace Gs2::Lottery::Request
{
    class FDescribeProbabilitiesByUserIdRequest;

    class GS2LOTTERY_API FDescribeProbabilitiesByUserIdRequest final : public TSharedFromThis<FDescribeProbabilitiesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LotteryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeProbabilitiesByUserIdRequest();
        FDescribeProbabilitiesByUserIdRequest(
            const FDescribeProbabilitiesByUserIdRequest& From
        );
        ~FDescribeProbabilitiesByUserIdRequest() = default;

        TSharedPtr<FDescribeProbabilitiesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeProbabilitiesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeProbabilitiesByUserIdRequest> WithLotteryName(const TOptional<FString> LotteryName);
        TSharedPtr<FDescribeProbabilitiesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeProbabilitiesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLotteryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeProbabilitiesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeProbabilitiesByUserIdRequest> FDescribeProbabilitiesByUserIdRequestPtr;
}