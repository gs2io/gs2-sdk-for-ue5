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

namespace Gs2::Mission::Request
{
    class FVerifyCounterValueRequest;

    class GS2MISSION_API FVerifyCounterValueRequest final : public TSharedFromThis<FVerifyCounterValueRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> ScopeTypeValue;
        TOptional<FString> ResetTypeValue;
        TOptional<FString> ConditionNameValue;
        TOptional<int64> ValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCounterValueRequest();
        FVerifyCounterValueRequest(
            const FVerifyCounterValueRequest& From
        );
        ~FVerifyCounterValueRequest() = default;

        TSharedPtr<FVerifyCounterValueRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCounterValueRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCounterValueRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyCounterValueRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FVerifyCounterValueRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCounterValueRequest> WithScopeType(const TOptional<FString> ScopeType);
        TSharedPtr<FVerifyCounterValueRequest> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FVerifyCounterValueRequest> WithConditionName(const TOptional<FString> ConditionName);
        TSharedPtr<FVerifyCounterValueRequest> WithValue(const TOptional<int64> Value);
        TSharedPtr<FVerifyCounterValueRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyCounterValueRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetScopeType() const;
        TOptional<FString> GetResetType() const;
        TOptional<FString> GetConditionName() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCounterValueRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCounterValueRequest> FVerifyCounterValueRequestPtr;
}