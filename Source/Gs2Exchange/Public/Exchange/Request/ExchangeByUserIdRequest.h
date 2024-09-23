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

namespace Gs2::Exchange::Request
{
    class FExchangeByUserIdRequest;

    class GS2EXCHANGE_API FExchangeByUserIdRequest final : public TSharedFromThis<FExchangeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FExchangeByUserIdRequest();
        FExchangeByUserIdRequest(
            const FExchangeByUserIdRequest& From
        );
        ~FExchangeByUserIdRequest() = default;

        TSharedPtr<FExchangeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FExchangeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FExchangeByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FExchangeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FExchangeByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FExchangeByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FExchangeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FExchangeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FExchangeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FExchangeByUserIdRequest, ESPMode::ThreadSafe> FExchangeByUserIdRequestPtr;
}