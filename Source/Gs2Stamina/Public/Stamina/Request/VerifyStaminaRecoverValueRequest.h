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
    class FVerifyStaminaRecoverValueRequest;

    class GS2STAMINA_API FVerifyStaminaRecoverValueRequest final : public TSharedFromThis<FVerifyStaminaRecoverValueRequest>
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
        
        FVerifyStaminaRecoverValueRequest();
        FVerifyStaminaRecoverValueRequest(
            const FVerifyStaminaRecoverValueRequest& From
        );
        ~FVerifyStaminaRecoverValueRequest() = default;

        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyStaminaRecoverValueRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

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

        static TSharedPtr<FVerifyStaminaRecoverValueRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyStaminaRecoverValueRequest> FVerifyStaminaRecoverValueRequestPtr;
}