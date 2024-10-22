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
    class FDecreaseMaxValueRequest;

    class GS2STAMINA_API FDecreaseMaxValueRequest final : public TSharedFromThis<FDecreaseMaxValueRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> DecreaseValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseMaxValueRequest();
        FDecreaseMaxValueRequest(
            const FDecreaseMaxValueRequest& From
        );
        ~FDecreaseMaxValueRequest() = default;

        TSharedPtr<FDecreaseMaxValueRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseMaxValueRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseMaxValueRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FDecreaseMaxValueRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDecreaseMaxValueRequest> WithDecreaseValue(const TOptional<int32> DecreaseValue);
        TSharedPtr<FDecreaseMaxValueRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetDecreaseValue() const;
        FString GetDecreaseValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseMaxValueRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaxValueRequest> FDecreaseMaxValueRequestPtr;
}