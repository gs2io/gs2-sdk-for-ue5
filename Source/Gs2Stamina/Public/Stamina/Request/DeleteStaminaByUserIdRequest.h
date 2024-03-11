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

namespace Gs2::Stamina::Request
{
    class FDeleteStaminaByUserIdRequest;

    class GS2STAMINA_API FDeleteStaminaByUserIdRequest final : public TSharedFromThis<FDeleteStaminaByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteStaminaByUserIdRequest();
        FDeleteStaminaByUserIdRequest(
            const FDeleteStaminaByUserIdRequest& From
        );
        ~FDeleteStaminaByUserIdRequest() = default;

        TSharedPtr<FDeleteStaminaByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteStaminaByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteStaminaByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FDeleteStaminaByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteStaminaByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteStaminaByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteStaminaByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteStaminaByUserIdRequest, ESPMode::ThreadSafe> FDeleteStaminaByUserIdRequestPtr;
}