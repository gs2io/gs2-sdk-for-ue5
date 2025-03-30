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
    class FVerifyStaminaRecoverValueByUserIdRequest;

    class GS2STAMINA_API FVerifyStaminaRecoverValueByUserIdRequest final : public TSharedFromThis<FVerifyStaminaRecoverValueByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> ValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyStaminaRecoverValueByUserIdRequest();
        FVerifyStaminaRecoverValueByUserIdRequest(
            const FVerifyStaminaRecoverValueByUserIdRequest& From
        );
        ~FVerifyStaminaRecoverValueByUserIdRequest() = default;

        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyStaminaRecoverValueByUserIdRequest> FVerifyStaminaRecoverValueByUserIdRequestPtr;
}