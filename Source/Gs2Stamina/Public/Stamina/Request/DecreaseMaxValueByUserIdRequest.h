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
    class FDecreaseMaxValueByUserIdRequest;

    class GS2STAMINA_API FDecreaseMaxValueByUserIdRequest final : public TSharedFromThis<FDecreaseMaxValueByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> DecreaseValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseMaxValueByUserIdRequest();
        FDecreaseMaxValueByUserIdRequest(
            const FDecreaseMaxValueByUserIdRequest& From
        );
        ~FDecreaseMaxValueByUserIdRequest() = default;

        TSharedPtr<FDecreaseMaxValueByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseMaxValueByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseMaxValueByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FDecreaseMaxValueByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDecreaseMaxValueByUserIdRequest> WithDecreaseValue(const TOptional<int32> DecreaseValue);
        TSharedPtr<FDecreaseMaxValueByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDecreaseMaxValueByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetDecreaseValue() const;
        FString GetDecreaseValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseMaxValueByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaxValueByUserIdRequest> FDecreaseMaxValueByUserIdRequestPtr;
}