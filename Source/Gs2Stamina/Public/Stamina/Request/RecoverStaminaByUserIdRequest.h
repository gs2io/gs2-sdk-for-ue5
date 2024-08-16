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
    class FRecoverStaminaByUserIdRequest;

    class GS2STAMINA_API FRecoverStaminaByUserIdRequest final : public TSharedFromThis<FRecoverStaminaByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> RecoverValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRecoverStaminaByUserIdRequest();
        FRecoverStaminaByUserIdRequest(
            const FRecoverStaminaByUserIdRequest& From
        );
        ~FRecoverStaminaByUserIdRequest() = default;

        TSharedPtr<FRecoverStaminaByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRecoverStaminaByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRecoverStaminaByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FRecoverStaminaByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRecoverStaminaByUserIdRequest> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FRecoverStaminaByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRecoverStaminaByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetRecoverValue() const;
        FString GetRecoverValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRecoverStaminaByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRecoverStaminaByUserIdRequest> FRecoverStaminaByUserIdRequestPtr;
}