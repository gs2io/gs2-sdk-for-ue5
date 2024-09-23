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
#include "../Model/Config.h"

namespace Gs2::Lottery::Request
{
    class FDrawWithRandomSeedByUserIdRequest;

    class GS2LOTTERY_API FDrawWithRandomSeedByUserIdRequest final : public TSharedFromThis<FDrawWithRandomSeedByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LotteryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> RandomSeedValue;
        TOptional<int32> CountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDrawWithRandomSeedByUserIdRequest();
        FDrawWithRandomSeedByUserIdRequest(
            const FDrawWithRandomSeedByUserIdRequest& From
        );
        ~FDrawWithRandomSeedByUserIdRequest() = default;

        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithLotteryName(const TOptional<FString> LotteryName);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithRandomSeed(const TOptional<int64> RandomSeed);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDrawWithRandomSeedByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLotteryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetRandomSeed() const;
        FString GetRandomSeedString() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDrawWithRandomSeedByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDrawWithRandomSeedByUserIdRequest, ESPMode::ThreadSafe> FDrawWithRandomSeedByUserIdRequestPtr;
}