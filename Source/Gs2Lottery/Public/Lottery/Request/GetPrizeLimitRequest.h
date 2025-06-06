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
    class FGetPrizeLimitRequest;

    class GS2LOTTERY_API FGetPrizeLimitRequest final : public TSharedFromThis<FGetPrizeLimitRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> PrizeIdValue;
        
    public:
        
        FGetPrizeLimitRequest();
        FGetPrizeLimitRequest(
            const FGetPrizeLimitRequest& From
        );
        ~FGetPrizeLimitRequest() = default;

        TSharedPtr<FGetPrizeLimitRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetPrizeLimitRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetPrizeLimitRequest> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FGetPrizeLimitRequest> WithPrizeId(const TOptional<FString> PrizeId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetPrizeId() const;

        static TSharedPtr<FGetPrizeLimitRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPrizeLimitRequest> FGetPrizeLimitRequestPtr;
}