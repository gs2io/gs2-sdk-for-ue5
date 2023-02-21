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
    class FConsumeStaminaRequest;

    class GS2STAMINA_API FConsumeStaminaRequest final : public TSharedFromThis<FConsumeStaminaRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> ConsumeValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FConsumeStaminaRequest();
        FConsumeStaminaRequest(
            const FConsumeStaminaRequest& From
        );
        ~FConsumeStaminaRequest() = default;

        TSharedPtr<FConsumeStaminaRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FConsumeStaminaRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FConsumeStaminaRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FConsumeStaminaRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FConsumeStaminaRequest> WithConsumeValue(const TOptional<int32> ConsumeValue);
        TSharedPtr<FConsumeStaminaRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetConsumeValue() const;
        FString GetConsumeValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FConsumeStaminaRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeStaminaRequest, ESPMode::ThreadSafe> FConsumeStaminaRequestPtr;
}