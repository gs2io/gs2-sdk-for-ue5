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
#include "../Model/Config.h"

namespace Gs2::Lottery::Request
{
    class FDrawByUserIdRequest;

    class GS2LOTTERY_API FDrawByUserIdRequest final : public TSharedFromThis<FDrawByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LotteryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDrawByUserIdRequest();
        FDrawByUserIdRequest(
            const FDrawByUserIdRequest& From
        );
        ~FDrawByUserIdRequest() = default;

        TSharedPtr<FDrawByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDrawByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDrawByUserIdRequest> WithLotteryName(const TOptional<FString> LotteryName);
        TSharedPtr<FDrawByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDrawByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FDrawByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FDrawByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDrawByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLotteryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDrawByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDrawByUserIdRequest> FDrawByUserIdRequestPtr;
}