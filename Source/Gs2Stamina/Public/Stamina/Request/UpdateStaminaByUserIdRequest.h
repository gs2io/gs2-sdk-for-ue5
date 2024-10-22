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
    class FUpdateStaminaByUserIdRequest;

    class GS2STAMINA_API FUpdateStaminaByUserIdRequest final : public TSharedFromThis<FUpdateStaminaByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> ValueValue;
        TOptional<int32> MaxValueValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<int32> RecoverValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateStaminaByUserIdRequest();
        FUpdateStaminaByUserIdRequest(
            const FUpdateStaminaByUserIdRequest& From
        );
        ~FUpdateStaminaByUserIdRequest() = default;

        TSharedPtr<FUpdateStaminaByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithMaxValue(const TOptional<int32> MaxValue);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateStaminaByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<int32> GetMaxValue() const;
        FString GetMaxValueString() const;
        TOptional<int32> GetRecoverIntervalMinutes() const;
        FString GetRecoverIntervalMinutesString() const;
        TOptional<int32> GetRecoverValue() const;
        FString GetRecoverValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateStaminaByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateStaminaByUserIdRequest> FUpdateStaminaByUserIdRequestPtr;
}