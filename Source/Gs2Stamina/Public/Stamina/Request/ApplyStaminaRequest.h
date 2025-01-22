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
    class FApplyStaminaRequest;

    class GS2STAMINA_API FApplyStaminaRequest final : public TSharedFromThis<FApplyStaminaRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FApplyStaminaRequest();
        FApplyStaminaRequest(
            const FApplyStaminaRequest& From
        );
        ~FApplyStaminaRequest() = default;

        TSharedPtr<FApplyStaminaRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FApplyStaminaRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FApplyStaminaRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FApplyStaminaRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FApplyStaminaRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FApplyStaminaRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FApplyStaminaRequest> FApplyStaminaRequestPtr;
}