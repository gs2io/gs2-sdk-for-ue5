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
    class FSetMaxValueByUserIdRequest;

    class GS2STAMINA_API FSetMaxValueByUserIdRequest final : public TSharedFromThis<FSetMaxValueByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> MaxValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetMaxValueByUserIdRequest();
        FSetMaxValueByUserIdRequest(
            const FSetMaxValueByUserIdRequest& From
        );
        ~FSetMaxValueByUserIdRequest() = default;

        TSharedPtr<FSetMaxValueByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetMaxValueByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetMaxValueByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FSetMaxValueByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetMaxValueByUserIdRequest> WithMaxValue(const TOptional<int32> MaxValue);
        TSharedPtr<FSetMaxValueByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetMaxValueByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetMaxValue() const;
        FString GetMaxValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetMaxValueByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetMaxValueByUserIdRequest> FSetMaxValueByUserIdRequestPtr;
}