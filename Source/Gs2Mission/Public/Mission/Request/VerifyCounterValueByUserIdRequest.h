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

namespace Gs2::Mission::Request
{
    class FVerifyCounterValueByUserIdRequest;

    class GS2MISSION_API FVerifyCounterValueByUserIdRequest final : public TSharedFromThis<FVerifyCounterValueByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> ScopeTypeValue;
        TOptional<FString> ResetTypeValue;
        TOptional<FString> ConditionNameValue;
        TOptional<int64> ValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCounterValueByUserIdRequest();
        FVerifyCounterValueByUserIdRequest(
            const FVerifyCounterValueByUserIdRequest& From
        );
        ~FVerifyCounterValueByUserIdRequest() = default;

        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithScopeType(const TOptional<FString> ScopeType);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithConditionName(const TOptional<FString> ConditionName);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithValue(const TOptional<int64> Value);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyCounterValueByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetScopeType() const;
        TOptional<FString> GetResetType() const;
        TOptional<FString> GetConditionName() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCounterValueByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCounterValueByUserIdRequest, ESPMode::ThreadSafe> FVerifyCounterValueByUserIdRequestPtr;
}