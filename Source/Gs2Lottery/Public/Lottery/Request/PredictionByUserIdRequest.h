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
    class FPredictionByUserIdRequest;

    class GS2LOTTERY_API FPredictionByUserIdRequest final : public TSharedFromThis<FPredictionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LotteryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> RandomSeedValue;
        TOptional<int32> CountValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPredictionByUserIdRequest();
        FPredictionByUserIdRequest(
            const FPredictionByUserIdRequest& From
        );
        ~FPredictionByUserIdRequest() = default;

        TSharedPtr<FPredictionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPredictionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPredictionByUserIdRequest> WithLotteryName(const TOptional<FString> LotteryName);
        TSharedPtr<FPredictionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPredictionByUserIdRequest> WithRandomSeed(const TOptional<int64> RandomSeed);
        TSharedPtr<FPredictionByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FPredictionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPredictionByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLotteryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetRandomSeed() const;
        FString GetRandomSeedString() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPredictionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPredictionByUserIdRequest, ESPMode::ThreadSafe> FPredictionByUserIdRequestPtr;
}