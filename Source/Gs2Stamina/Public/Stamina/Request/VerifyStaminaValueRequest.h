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

namespace Gs2::Stamina::Request
{
    class FVerifyStaminaValueRequest;

    class GS2STAMINA_API FVerifyStaminaValueRequest final : public TSharedFromThis<FVerifyStaminaValueRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> ValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyStaminaValueRequest();
        FVerifyStaminaValueRequest(
            const FVerifyStaminaValueRequest& From
        );
        ~FVerifyStaminaValueRequest() = default;

        TSharedPtr<FVerifyStaminaValueRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyStaminaValueRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyStaminaValueRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyStaminaValueRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FVerifyStaminaValueRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyStaminaValueRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FVerifyStaminaValueRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyStaminaValueRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyStaminaValueRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyStaminaValueRequest> FVerifyStaminaValueRequestPtr;
}