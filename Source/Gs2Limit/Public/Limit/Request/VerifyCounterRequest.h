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

namespace Gs2::Limit::Request
{
    class FVerifyCounterRequest;

    class GS2LIMIT_API FVerifyCounterRequest final : public TSharedFromThis<FVerifyCounterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> LimitNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CountValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCounterRequest();
        FVerifyCounterRequest(
            const FVerifyCounterRequest& From
        );
        ~FVerifyCounterRequest() = default;

        TSharedPtr<FVerifyCounterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCounterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCounterRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyCounterRequest> WithLimitName(const TOptional<FString> LimitName);
        TSharedPtr<FVerifyCounterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FVerifyCounterRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCounterRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FVerifyCounterRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyCounterRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetLimitName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCounterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCounterRequest> FVerifyCounterRequestPtr;
}