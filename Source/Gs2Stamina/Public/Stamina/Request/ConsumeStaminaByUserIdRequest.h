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
    class FConsumeStaminaByUserIdRequest;

    class GS2STAMINA_API FConsumeStaminaByUserIdRequest final : public TSharedFromThis<FConsumeStaminaByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> ConsumeValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeStaminaByUserIdRequest();
        FConsumeStaminaByUserIdRequest(
            const FConsumeStaminaByUserIdRequest& From
        );
        ~FConsumeStaminaByUserIdRequest() = default;

        TSharedPtr<FConsumeStaminaByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeStaminaByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeStaminaByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FConsumeStaminaByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FConsumeStaminaByUserIdRequest> WithConsumeValue(const TOptional<int32> ConsumeValue);
        TSharedPtr<FConsumeStaminaByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FConsumeStaminaByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetConsumeValue() const;
        FString GetConsumeValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeStaminaByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeStaminaByUserIdRequest> FConsumeStaminaByUserIdRequestPtr;
}