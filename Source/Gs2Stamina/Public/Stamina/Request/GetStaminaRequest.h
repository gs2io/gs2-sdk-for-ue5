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
    class FGetStaminaRequest;

    class GS2STAMINA_API FGetStaminaRequest final : public TSharedFromThis<FGetStaminaRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetStaminaRequest();
        FGetStaminaRequest(
            const FGetStaminaRequest& From
        );
        ~FGetStaminaRequest() = default;

        TSharedPtr<FGetStaminaRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStaminaRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStaminaRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FGetStaminaRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetStaminaRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStaminaRequest> FGetStaminaRequestPtr;
}